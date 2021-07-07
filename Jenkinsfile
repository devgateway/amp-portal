#!groovy

// Important: What is BRANCH_NAME?
// It is branch name for builds triggered from branches.
// It is PR-<pr-id> for builds triggered from pull requests.
def tag
if (BRANCH_NAME ==~ /feature\/AMPP-\d+.*/) {
    def jiraId = (BRANCH_NAME =~ /feature\/AMP-(\d+).*/)[0][1]
    tag = "feature-${jiraId}"
} else {
    tag = BRANCH_NAME.replaceAll(/[^a-zA-Z0-9_-]/, "-").toLowerCase()
}

// Record original branch or pull request for cleanup jobs
def branch = env.CHANGE_ID == null ? BRANCH_NAME : null
def pr = env.CHANGE_ID
//def registryKey = env.AMP_REGISTRY_PRIVATE_KEY
def changePretty = (pr != null) ? "pull request ${pr}" : "branch ${branch}"

println "Branch: ${branch}"
println "Pull request: ${pr}"
println "Tag: ${tag}"

def launchedByUser = currentBuild.getBuildCauses('hudson.model.Cause$UserIdCause').size() > 0
def codeVersion
def countries
def country
def ampppHost
def ampppUrl
stage('Build') {
  node {
    // Find AMP version
    //codeVersion = readMavenPom(file: 'amp/pom.xml').version
    codeVersion = 4.0;
    println "AMP Public Portal Version: ${codeVersion}"

    countries = sh(returnStdout: true,
          script: "ssh sulfur.migrated.devgateway.org 'cd /opt/amppp_dbs && amppp-db ls ${codeVersion} | sort'")
          .trim()
          if (countries == "") {
          println "There are no database backups compatible with ${codeVersion}"
          currentBuild.result = 'FAILURE'
          }
    if (country == null) {
        timeout(15) {
            milestone()
            country = input(
                    message: "Proceed with build and deploy?",
                    parameters: [choice(choices: countries, name: 'country')])
            milestone()
        }
    }
    ampppHost="http://wp.amppp-${country}-${tag}-tc9.ampsite.net"
    ampppUrl = "http://amppp-${country}-${tag}-tc9.ampsite.net/"

    println "ampppUrl: ${ampppUrl}"

        checkout scm

        def format = branch != null ? "%H" : "%P"
        def hash = sh(returnStdout: true, script: "git log --pretty=${format} -n 1").trim()
        sh(returnStatus: true, script: "docker pull phosphorus.migrated.devgateway.org:5000/amppp-ui:${tag} > /dev/null")
        def imageIds = sh(returnStdout: true, script: "docker images -q -f \"label=git-hash=${hash}\"").trim()
        println "imageIds:${imageIds}"
        sh(returnStatus: true, script: "docker rmi phosphorus.migrated.devgateway.org:5000/amppp-ui:${tag} > /dev/null")
        imageIds = ""
        //Force build in the meantime
        if (imageIds.equals("")) { //If not found we build
          withEnv(["PATH+NODE=${tool name: 'node-12.16.3', type: 'jenkins.plugins.nodejs.tools.NodeJSInstallation'}/bin"]) {
          sh 'node -v'
                try {
                    // Build AMP Public Portal UI
                    // We build react lib
                    sh returnStatus: true, script: 'tar -xf ../amppp-node-cache.tar'
                    sh returnStatus: true, script: 'tar -xf ../amppp-lib-node-cache.tar'
                    sh returnStatus: true, script: 'tar -xf ../amppp-plugin-node-cache.tar'
                    sh "cd wp-react-lib && npm install"
                    sh "cd wp-react-lib && npm run dist"
                    sh "rm -f ./portal-ui/.env.production"
                    sh "echo \"REACT_APP_API_URL='https://amp-haiti-pr-3770-tc9.ampsite.net/rest\" >> ./portal-ui/.env.production"
                    sh "echo \"REACT_APP_WP_URL='https:/wp./amp-haiti-pr-3770-tc9.ampsite.net\" >> ./portal-ui/.env.production"
                    sh "cd portal-ui && npm install"
                    sh "cd portal-ui && npm run build --host=${ampppHost}"

                    sh returnStatus: true, script: "tar -cf ../amppp-node-cache.tar --remove-files" +
                            " ./portal-ui/node_modules"
                    sh returnStatus: true, script: "tar -cf ../amppp-lib-node-cache.tar --remove-files" +
                            " ./wp-react-lib/node_modules"


                    // Build Docker images & push it
                    println "tag:${tag}"
                    println "PR:${pr}"
                    println "branch:${branch}"
                    println "hash:${hash}"

                    //replace to build in
                    sh "docker build -q -t phosphorus.migrated.devgateway.org:5000/amppp-ui:${tag} --build-arg AMPPP_UI=portal-ui/build --build-arg AMPPP_PULL_REQUEST='${pr}' --build-arg AMPPP_BRANCH='${branch}' --label git-hash='${hash}' ."
                    sh "docker push phosphorus.migrated.devgateway.org:5000/amppp-ui:${tag} > /dev/null"
                    sh "cp -R wp-content amppp-wp"

                    sh "cp -R wp-theme/ amppp-wp/wp-content/themes/"

                    sh "mv amppp-wp/wp-content/themes/wp-theme amppp-wp/wp-content/themes/dg-semantic"

                    sh "cd wp-react-blocks-plugin/blocks && npm install"
                    sh "cd wp-react-blocks-plugin/blocks && npm run build"

                    sh returnStatus: true, script: "tar -cf ../amppp-plugin-node-cache.tar --remove-files" +
                            " ./wp-react-blocks-plugin/blocks/node_modules"

                    sh 'mkdir ./amppp-wp/wp-content/plugins/wp-react-blocks-plugin'
                    sh 'mkdir ./amppp-wp/wp-content/plugins/wp-react-blocks-plugin/blocks'
                    sh 'mkdir ./amppp-wp/wp-content/plugins/wp-react-blocks-plugin/blocks/build'
               
                    sh "cp ./wp-react-blocks-plugin/blocks/build/* ./amppp-wp/wp-content/plugins/wp-react-blocks-plugin/blocks/build"
                    sh 'cp ./wp-react-blocks-plugin/index.php ./amppp-wp/wp-content/plugins/wp-react-blocks-plugin'

                    //This should be moved to our own wp image
                    //sh "cp ../wp-cli.phar amppp-wp/"
                    //sh "cd amppp-wp && curl -O https://raw.githubusercontent.com/wp-cli/builds/gh-pages/phar/wp-cli.phar"
                    //sh "cd amppp-wp && chmod +x wp-cli.phar"

                    sh "docker build -q -t phosphorus.migrated.devgateway.org:5000/amppp-wp:${tag} --build-arg AMPPP_PULL_REQUEST='${pr}' --build-arg AMPPP_BRANCH='${branch}' --label git-hash='${hash}' amppp-wp"
                    sh "docker push phosphorus.migrated.devgateway.org:5000/amppp-wp:${tag} > /dev/null"
                } finally {

                    // Cleanup after Docker & Maven
                    sh "rm -fr amppp-wp/wp-content"

                    sh returnStatus: true, script: "docker rmi phosphorus.migrated.devgateway.org:5000/amppp-ui:${tag}"
                    sh returnStatus: true, script: "docker rmi phosphorus.migrated.devgateway.org:5000/amppp-wp:${tag}"
                }
            }
        }else{
          println "Image already foound skiping build ${imageIds}"

        }
    }
}

// If this stage fails then next stage will retry deployment. Otherwise next stage will be skipped.
stage('Deploy') {
    node {
        try {
            // Find latest database version compatible with ${codeVersion}
            dbVersion = sh(returnStdout: true, script: "ssh sulfur.migrated.devgateway.org 'cd /opt/amppp_dbs && amppp-db find ${codeVersion} ${country}'").trim()

            // Deploy AMPP
            println "Deploying amp"
            sh "ssh sulfur.migrated.devgateway.org 'cd /opt/docker/amppp && ./up.sh ${tag} ${country} ${dbVersion}'"

            slackSend(channel: 'amp-ci', color: 'good', message: "Deploy AMP Public Portal - Success\nDeployed ${changePretty} will be ready for testing at ${ampppUrl} in about 3 minutes")

            deployed = true
        } catch (e) {
            slackSend(channel: 'amp-ci', color: 'warning', message: "Deploy AMP - Failed\nFailed to deploy ${changePretty}")

            currentBuild.result = 'UNSTABLE'
        }
    }
}

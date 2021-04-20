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

    ampUrl = "http://amp-${country}-${tag}-tc9.ampsite.net/"

    println "ampUrl: ${ampUrl}"

        checkout scm

        def format = branch != null ? "%H" : "%P"
        def hash = sh(returnStdout: true, script: "git log --pretty=${format} -n 1").trim()
        //sh(returnStatus: true, script: "docker pull phosphorus.migrated.devgateway.org:5000/am ppp-webapp:${tag} > /dev/null")
        def imageIds = sh(returnStdout: true, script: "docker images -q -f \"label=git-hash=${hash}\"").trim()
        //sh(returnStatus: true, script: "docker rmi phosphorus.migrated.devgateway.org:5000/amppp-webapp:${tag} > /dev/null")

        if (imageIds.equals("")) { //If not found we build
          withEnv(["PATH+NODE=${tool name: 'node-12.16.3', type: 'jenkins.plugins.nodejs.tools.NodeJSInstallation'}/bin"]) {
          sh 'node -v'
                try {
                    // Build AMP Public Portal UI
                    sh returnStatus: true, script: 'tar -xf ../amppp-node-cache.tar'
                    sh "cd ui && npm install"
                    sh "cd ui && npm run build"

                    sh returnStatus: true, script: "tar -cf ../amp-node-cache.tar --remove-files" +
                            " ./ui/node_modules"



                    // Build Docker images & push it
                    //sh "docker build -q -t phosphorus.migrated.devgateway.org:5000/amp-webapp:${tag} --build-arg AMP_EXPLODED_WAR=target/amp --build-arg AMP_PULL_REQUEST='${pr}' --build-arg AMP_BRANCH='${branch}' --build-arg AMP_REGISTRY_PRIVATE_KEY='${registryKey}' --label git-hash='${hash}' amp"
                    //sh "docker push phosphorus.migrated.devgateway.org:5000/amp-webapp:${tag} > /dev/null"
                } finally {

                    // Cleanup after Docker & Maven
                    //sh returnStatus: true, script: "docker rmi phosphorus.migrated.devgateway.org:5000/amppp-webapp:${tag}"
                }
            }
        }
    }
}

// If this stage fails then next stage will retry deployment. Otherwise next stage will be skipped.
stage('Deploy') {
    node {
        try {
            // Find latest database version compatible with ${codeVersion}
            dbVersion = sh(returnStdout: true, script: "ssh sulfur.migrated.devgateway.org 'cd /opt/amppp_dbs && amp-db find ${codeVersion} ${country}'").trim()

            // Deploy AMPP
            //sh "ssh sulfur.migrated.devgateway.org 'cd /opt/docker/amp && ./up.sh ${tag} ${country} ${dbVersion}'"

            slackSend(channel: 'amp-ci', color: 'good', message: "Deploy AMP Public Portal - Success\nDeployed ${changePretty} will be ready for testing at ${ampUrl} in about 3 minutes")

            deployed = true
        } catch (e) {
            slackSend(channel: 'amp-ci', color: 'warning', message: "Deploy AMP - Failed\nFailed to deploy ${changePretty}")

            currentBuild.result = 'UNSTABLE'
        }
    }
}

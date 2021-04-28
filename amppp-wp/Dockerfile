#UI image
FROM wordpress:5.7
ARG AMPPP_PULL_REQUEST
ARG AMPPP_BRANCH

LABEL "pull-request"=$AMPPP_PULL_REQUEST
LABEL "branch"=$AMPPP_BRANCH
#RUN apk add --update bash && rm -rf /var/cache/apk/*
ADD wp-cli.phar bin/wp
COPY update_host.sh bin/
run chmod +x /bin/update_host.sh
ADD ./wp-content /var/www/html/wp-content

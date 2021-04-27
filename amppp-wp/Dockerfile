#UI image
FROM wordpress:5.7
ARG AMPPP_PULL_REQUEST
ARG AMPPP_BRANCH

LABEL "pull-request"=$AMPPP_PULL_REQUEST
LABEL "branch"=$AMPPP_BRANCH
#RUN apk add --update bash && rm -rf /var/cache/apk/*
RUN curl -O https://raw.githubusercontent.com/wp-cli/builds/gh-pages/phar/wp-cli.phar
RUN chmod +x wp-cli.phar
mv wp-cli.phar /usr/local/bin/wp
ADD update_host.sh bin/
ADD ./wp-content /var/www/html/wp-content

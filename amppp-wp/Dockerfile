#UI image
FROM wordpress:5.7
ARG AMPPP_PULL_REQUEST
ARG AMPPP_BRANCH

LABEL "pull-request"=$AMPPP_PULL_REQUEST
LABEL "branch"=$AMPPP_BRANCH
#RUN apk add --update bash && rm -rf /var/cache/apk/*

RUN  mkdir /var/www && mkdir /var/www/ui
ADD ./wp_content:/var/www/html/wp-content

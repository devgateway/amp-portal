#UI image
FROM nginx:alpine
ARG AMPPP_UI
ARG AMPPP_PULL_REQUEST
ARG AMPPP_BRANCH


LABEL "pull-request"=$AMPPP_PULL_REQUEST
LABEL "branch"=$AMPPP_BRANCH
RUN apk add --update bash && rm -rf /var/cache/apk/*

RUN  mkdir /var/www && mkdir /var/www/ui
add ./amppp-ui/nginx/ui.conf /etc/nginx/conf.d/ui.conf
add ./amppp-ui/nginx/nginx.conf /etc/nginx/nginx.conf
ADD $AMPPP_UI /var/www/ui

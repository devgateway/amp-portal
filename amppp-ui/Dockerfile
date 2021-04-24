FROM nginx:alpine
ARG AMPPP_UI
ARG AMPPP_PULL_REQUEST
ARG AMPPP_BRANCH


LABEL "pull-request"=$AMPPP_PULL_REQUEST
LABEL "branch"=$AMPPP_BRANCH

RUN  mkdir /var/www/ui

ADD $AMPPP_UI /var/www/ui

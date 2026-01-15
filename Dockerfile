FROM	alpine:latest

RUN		apk add --no-cache \
		build-base \
		linux-headers \
		bash

WORKDIR	/app
COPY	. .

RUN		make re

CMD ["/bin/sh"]

FROM ubuntu:latest

RUN apt-get update \
    && apt-get install -y \
    net-tools \
    ncat \
    gcc \
    gdb \
    nano \
    vim \
    && apt-get clean \
    && rm -rf /var/lib/apt/lists/*

RUN mkdir /app
COPY flag.c /app/flag.c
COPY encrypt.h /app/encrypt.h
COPY decrypt.c /app/decrypt.c
COPY start.sh /app/start.sh
COPY flag.enc /app/flag.enc

WORKDIR /app
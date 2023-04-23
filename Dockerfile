FROM ubuntu:latest

RUN apt-get update \
    && apt-get install -y \
    openssh-server \
    #net-tools \
    ncat \
    gcc \
    gdb \
    nano \
    vim \
    && apt-get clean \
    && rm -rf /var/lib/apt/lists/*

# thanks for the help John!!!
RUN adduser --disabled-password --gecos "" labuser && echo 'labuser:labuser' | chpasswd
RUN mkdir /app
COPY flag.c /app/flag.c
COPY encrypt.h /app/encrypt.h
COPY decrypt.c /app/decrypt.c
COPY start.sh /app/start.sh
COPY flag.enc /app/flag.enc

WORKDIR /app

ENTRYPOINT bash start.sh && service ssh start && tail -f /dev/null

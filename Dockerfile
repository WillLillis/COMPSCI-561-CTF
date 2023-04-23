FROM ubuntu:latest

RUN apt-get update \
    && apt-get install -y \
    openssh-server \
    ncat \
    gcc \
    gdb \
    nano \
    vim \
    && apt-get clean \
    && rm -rf /var/lib/apt/lists/*

# thanks for the help John!!!
RUN adduser --disabled-password --gecos "" labuser && echo 'labuser:labuser' | chpasswd
COPY flag.c /home/labuser/flag.c
COPY encrypt.h /home/labuser/encrypt.h
COPY decrypt.c /home/labuser/decrypt.c
RUN chmod 777 /home/labuser/decrypt.c
COPY start.sh /home/labuser/start.sh
COPY flag.enc /home/labuser/flag.enc

WORKDIR /home/labuser

ENTRYPOINT bash start.sh && service ssh start && tail -f /dev/null

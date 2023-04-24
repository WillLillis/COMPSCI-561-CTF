FROM ubuntu:latest

RUN apt-get update \
    && apt-get install -y \
    openssh-server \
    gcc \
    gdb \
    nano \
    vim \
    emacs \
    && apt-get clean \
    && rm -rf /var/lib/apt/lists/*

# thanks for the help John!!!
RUN adduser --disabled-password --gecos "" labuser && echo 'labuser:labuser' | chpasswd
COPY flag.c /home/labuser/flag.c
COPY encrypt.h /home/labuser/encrypt.h
COPY base64.h /home/labuser/base64.h
COPY decrypt.c /home/labuser/decrypt.c
RUN chmod 777 /home/labuser/decrypt.c
COPY start.sh /home/labuser/start.sh
COPY flag.enc /home/labuser/flag.enc

WORKDIR /home/labuser

ENTRYPOINT bash start.sh && service ssh start && tail -f /dev/null

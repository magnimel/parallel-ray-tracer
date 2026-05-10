FROM ubuntu:24.04

ENV DEBIAN_FRONTEND=noninteractive

RUN apt-get update && apt-get install -y \
    build-essential \
    cmake \
    git \
    gdb \
    linux-tools-common \
    linux-tools-generic \
    linux-tools-virtual \
    sudo \
    vim \
    python3 \
    python3-pip \
    && rm -rf /var/lib/apt/lists/*

WORKDIR /workspace

CMD ["tail", "-f", "/dev/null"]
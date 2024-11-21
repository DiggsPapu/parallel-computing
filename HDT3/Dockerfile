# This image to handle the nvidia image with cuda toolkit development
FROM nvidia/cuda:11.8.0-devel-ubuntu22.04

# The working directory
WORKDIR /parallel_computing/
# SYSTEM
RUN apt-get update --yes --quiet && DEBIAN_FRONTEND=noninteractive apt-get install --yes --quiet --no-install-recommends \
    software-properties-common \
    build-essential apt-utils \
    wget curl vim git ca-certificates kmod \
    nvidia-driver-525 \
 && rm -rf /var/lib/apt/lists/*

 RUN apt-get update -y && \
     apt-get upgrade -y && \
     apt-get install -y curl build-essential libopenmpi-dev openmpi-bin mpich
 
 COPY . .
 
 CMD [ "/bin/bash" ]
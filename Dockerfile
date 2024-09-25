FROM ubuntu:22.04
WORKDIR /parallel_computing/

RUN apt-get update -y && \
    apt-get upgrade -y && \
    apt-get install -y curl build-essential libopenmpi-dev openmpi-bin mpich && \
    useradd -ms /bin/bash mpiuser

USER mpiuser
COPY . .

CMD [ "/bin/bash" ]

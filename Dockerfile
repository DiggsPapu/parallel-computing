FROM ubuntu:22.04
WORKDIR /parallel_computing/
  
RUN apt-get update -y && \
    apt-get upgrade -y && \
    apt-get install -y curl && \
    apt-get install build-essential -y

COPY . .

CMD [ "/bin/bash" ]
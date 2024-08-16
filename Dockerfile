FROM ubuntu:22.04
WORKDIR /parallel_computing/
  
RUN apt-get update -y && \
    apt-get upgrade -y && \
    apt-get install -y curl && \
    apt-get install build-essential -y

COPY . .

CMD [ "/bin/bash" ]

# Naming the image
# docker build -t parallel_computing .

# Naming the container env
# docker run -it --name=parallel_computing_name parallel_computing

# Run docker env set name and pwd
# docker run -it --name=parallel_computing -v $(pwd):/parallel_computing parallel_computing

# Run docker env
# docker start parallel_computing
# docker exec -it parallel_computing /bin/bash

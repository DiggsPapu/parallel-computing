# Parallel Computing

Diego Andrés Alonzo Medinilla 20172

## How to build the env?
- Naming the image:
    ```bash
    docker build -t parallel_computing .
    ```
- Naming the container env:
    ```bash
    docker run -it --name=parallel_computing parallel_computing
    ```
- Run docker env set name and pwd:
    ```bash
    docker run -it --name=parallel_computing -v $(pwd):/parallel_computing parallel_computing
    ```
- Run docker env:
    ```bash
    docker start parallel_computing
    
    docker exec -it parallel_computing /bin/bash
    ```
## How to run the files?

- Ex 1:
    - Compilation && Execution
        ```bash
        make run
        ```
    - Cleaning 
        ```bash    
        make clean
        ```
- Ex 2:
    - Compilation && Execution
        ```bash
        make -f Makefile2 run
        ```
    - Cleaning 
        ```bash    
        make -f Makefile2 clean
        ```
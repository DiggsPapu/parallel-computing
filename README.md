# Parallel Computing

Diego Andrés Alonzo Medinilla 20172

## How to build the env?
- Naming the image:

    docker build -t parallel_computing .

- Naming the container env:

    docker run -it --name=parallel_computing parallel_computing

- Run docker env set name and pwd:

    docker run -it --name=parallel_computing -v $(pwd):/parallel_computing parallel_computing

- Run docker env:

    docker start parallel_computing
    
    docker exec -it parallel_computing /bin/bash

## How to run the files?

- Ex 1:
    - Compilation

        g++ Ejercicio1.cpp -o Ejercicio1
    - Execution
        
        ./Ejercicio1

- Ex 2:
    - Compilation
    
        g++ Ejercicio2.cpp -fopenmp -o Ejercicio2
    - Execution

        ./Ejercicio2

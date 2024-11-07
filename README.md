# HDT 3

## ¿Cómo levantar el contenedor?
### Construir el contenedor
```bash
docker build -t parallel_computing .
```
### Levantar el contenedor
```bash
docker run --gpus all -it --name=parallel_computing -v $(pwd):/parallel_computing parallel_computing
```
### Levantar el contenedor cuando ya se creo el contenedor
```bash
docker start -i parallel_computing
```
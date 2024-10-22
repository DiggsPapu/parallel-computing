# Parallel Computing

- Diego Andrés Alonzo Medinilla 20172

## ¿Cómo levantar el contenedor?
### Construir el contenedor
```bash
docker build -t parallel_computing .
```
### Levantar el contenedor
```bash
docker run -it --name=parallel_computing -v $(pwd):/parallel_computing parallel_computing
```
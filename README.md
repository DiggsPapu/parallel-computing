# HDT 3

## ¿Cómo levantar el contenedor?
### Construir el contenedor
```bash
docker build -t paralela-proyecto-3 .
```
### Levantar el contenedor
```bash
docker run -it --name=paralela-proyecto-3 -v $(pwd):/parallel_computing paralela-proyecto-3
```
### Levantar el contenedor cuando ya se creo el contenedor
```bash
docker start -i paralela-proyecto-3
```
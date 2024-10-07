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
## Pregunta 1

a. Check_for_error() Esta se utiliza para verificar si algún proceso ha encontrado un error, esto debido a que cada proceso puede tener un estado diferente y es imperativo que se comuniquen para detectar errores en el sistema.

b. Read_n() Esta función se encarga de obtener el orden de los vectores en el proceso 0 y enviar un broadcast (comunicarlo) a los otros procesos.

c. Read_data() esta función sirve para leer un vector en el proceso 0 y distribuirlo en los procesos utilizando un bloque de distribución.

d. Print_vector()  esta funci[on se encarga de imprimir un vector que tiene un bloque de distribución en stdout.
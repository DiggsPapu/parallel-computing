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

## Pregunta 2

<table>
    <thead>
        <th>Secuencial</th>
        <th>Paralela</th>
        <th>Speedup</th>
    </thead>
    <tbody>
        <tr>
            <td>4.996000</td>
            <td>6.240508</td>
            <td>0.801802</td>
        </tr>
        <tr>
            <td>4.219000</td>
            <td>4.651753</td>
            <td>0.907056</td>
        </tr>
        <tr>
            <td>4.493000</td>
            <td>6.145043</td>
            <td>0.731062</td>
        </tr>
        <tr>
            <td>4.323000</td>
            <td>4.374057</td>
            <td>0.987295</td>
        </tr>
        <tr>
            <td>4.814000</td>
            <td>4.498931</td>
            <td>1.071025</td>
        </tr>
        <tr>
            <td>5.355000</td>
            <td>6.010994</td>
            <td>0.890619</td>
        </tr>
        <tr>
            <td>4.532000</td>
            <td>4.544585</td>
            <td>0.998969</td>
        </tr>
        <tr>
            <td>4.244000</td>
            <td>6.960463</td>
            <td>0.609041</td>
        </tr>
        <tr>
            <td>4.763000</td>
            <td>6.211874</td>
            <td>0.766568</td>
        </tr>
        <tr>
            <td>4.354000</td>
            <td>6.657810</td>
            <td>0.654538</td>
        </tr>
    </tbody>
</table>

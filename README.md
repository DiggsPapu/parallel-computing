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
### Paralela 
![alt text](image.png)

<table>
    <thead>
        <th>Secuencial (ms)</th>
        <th>Paralela (ms)</th>
        <th>Speedup</th>
    </thead>
    <tbody>
        <tr>
            <td>4154.603000</td>
            <td>5976.773385</td>
            <td>0.694811</td>
        </tr>
        <tr>
            <td>4808.581000</td>
            <td>4619.429738</td>
            <td>1.041066</td>
        </tr>
        <tr>
            <td>5948.869000</td>
            <td>5672.692309</td>
            <td>1.048586</td>
        </tr>
        <tr>
            <td>4367.314000</td>
            <td>6014.467925</td>
            <td>0.725844</td>
        </tr>
        <tr>
            <td>4814.000000</td>
            <td>5057.870294</td>
            <td>0.950391</td>
        </tr>
        <tr>
            <td>4839.353000</td>
            <td>5272.062483</td>
            <td>0.916920</td>
        </tr>
        <tr>
            <td>3939.731000</td>
            <td>6284.705381</td>
            <td>0.626297</td>
        </tr>
        <tr>
            <td>5779.955000</td>
            <td>6040.599925</td>
            <td>0.957248</td>
        </tr>
        <tr>
            <td>5263.288000</td>
            <td>4390.810820</td>
            <td>1.196584</td>
        </tr>
        <tr>
            <td>4698.957000</td>
            <td>5861.174549</td>
            <td>0.801787</td>
        </tr>
    </tbody>
</table>

Promedio 0.8959534000000001

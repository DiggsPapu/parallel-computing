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

## Ejecuciones

### Riemann
![alt text](image.png)

### MP
![alt text](image-2.png)

### MPI
![alt text](image-1.png)

## Speed ups
<!DOCTYPE html>
<html lang="es">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Tablas de Resultados</title>
    <style>
        table {
            width: 60%;
            border-collapse: collapse;
            margin: 20px auto;
            font-family: Arial, sans-serif;
        }
        th, td {
            border: 1px solid #ddd;
            padding: 8px;
            text-align: center;
        }
        th {
            background-color: black;
        }
        tr:hover {
            background-color: grey;
        }
    </style>
</head>
<body>

<h2 style="text-align: center;">Tiempos de Ejecución</h2>
<table>
    <thead>
        <tr>
            <th>Secuencial</th>
            <th>MP</th>
            <th>MPI</th>
        </tr>
    </thead>
    <tbody>
        <tr>
            <td>0.109194</td>
            <td>0.028471</td>
            <td>0.010759</td>
        </tr>
        <tr>
            <td>0.07006</td>
            <td>0.028849</td>
            <td>0.007419</td>
        </tr>
        <tr>
            <td>0.09001</td>
            <td>0.033646</td>
            <td>0.007689</td>
        </tr>
        <tr>
            <td>0.089754667</td>
            <td>0.030322</td>
            <td>0.008622333</td>
        </tr>
    </tbody>
</table>

<h2 style="text-align: center;">Speedup</h2>
<table>
    <thead>
        <tr>
            <th>Speedup MP vs Secuencial</th>
            <th>Speedup MPI vs Secuencial</th>
            <th>Speedup MPI vs MP</th>
        </tr>
    </thead>
    <tbody>
        <tr>
            <td>3.835270977</td>
            <td>10.14908449</td>
            <td>2.646249651</td>
        </tr>
        <tr>
            <td>2.428507054</td>
            <td>9.443321202</td>
            <td>3.888529451</td>
        </tr>
        <tr>
            <td>2.675206562</td>
            <td>11.70633372</td>
            <td>4.37586162</td>
        </tr>
        <tr>
            <td>2.979661531</td>
            <td>10.43291314</td>
            <td>3.636880241</td>
        </tr>
    </tbody>
</table>

</body>
</html>

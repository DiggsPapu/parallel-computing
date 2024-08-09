# Lab 1

Diego Andrés Alonzo Medinilla 20172

## Ex 1

![alt text](image-9.png)

Los mensajes no están desplegados en orden debido a que al ser threads puede que unos threads lleguen antes que otros threads.

## Ex 2

![alt text](image-10.png)

## Ex 3

Para X^2 con a = 2 y b = 10 y n = 10^6: 

![alt text](image.png)

Para 2X^3 con a = 3 y b = 7 y n = 10^6:

![alt text](image-1.png)

Para sin(x) con a = 0 y b = 1 y n = 10^6:

![alt text](image-2.png)

## Ex 4

Para X^2 con a = 2 y b = 10 y n = 10^6 y threads = 10: 

![alt text](image-4.png)

Para 2X^3 con a = 3 y b = 7 y n = 10^6 y threads = 10:

![alt text](image-5.png)

Para sin(x) con a = 0 y b = 1 y n = 10^6 y threads = 10:

![alt text](image-3.png)

El uso de pragma critical es para garantizar que al momento de acceder memoria compartida, en este caso el resultado solo una pueda modificarlo en ese momento de manera que la información sea concisa.

## Ex 5

Para X^2 con a = 2 y b = 10 y n = 10^6 y threads = 10: 

![alt text](image-7.png)

Para 2X^3 con a = 3 y b = 7 y n = 10^6 y threads = 10:

![alt text](image-8.png)

Para sin(x) con a = 0 y b = 1 y n = 10^6 y threads = 10:

![alt text](image-6.png)

Existe diferencia entre usar una variable global y un arreglo, debido a que en primer lugar la variable global previene que hayan raise conditions. Así mismo, hay que hacer una secuencia para unión de datos finales. Sin embargo, también se debe de denotar que se tiene un peor resultado utilizando un arreglo dado que las aproximaciones fueron peores.
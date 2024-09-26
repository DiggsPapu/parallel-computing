#include <stdio.h>
#include <stdlib.h>
#include <time.h>  // Incluir la biblioteca para medir el tiempo

int main() {
    FILE *file;
    int *array;
    int size = 0;  // Tamaño del array, se determinará dinámicamente
    int sum = 0;
    int max, min;
    float promedio;
    int valor;

    // Comenzar a medir el tiempo
    clock_t start_time = clock();  // Guardar el tiempo de inicio

    // Abrir el archivo
    file = fopen("numeros_aleatorios.txt", "r");
    if (file == NULL) {
        printf("Error al abrir el archivo\n");
        return 1;
    }

    // Primera pasada: contar cuántos números hay en el archivo
    while (fscanf(file, "%d", &valor) == 1) {
        size++;
    }

    // Asignar memoria para el array dinámico una vez conocido el tamaño
    array = (int*)malloc(size * sizeof(int));

    if (array == NULL) {
        printf("Error al asignar memoria\n");
        fclose(file);
        return 1;
    }

    // Volver a abrir el archivo para cargar los valores
    rewind(file);  // Regresar al inicio del archivo

    // Segunda pasada: leer los valores y cargarlos en el array
    for (int i = 0; i < size; i++) {
        fscanf(file, "%d", &array[i]);
    }

    // Cerrar el archivo
    fclose(file);

    // Inicializar max y min
    max = array[0];
    min = array[0];

    // Procesar el array secuencialmente (suma, max, min, promedio)
    for (int i = 0; i < size; i++) {
        valor = array[i];
        sum += valor;
        
        if (valor > max) {
            max = valor;
        }
        if (valor < min) {
            min = valor;
        }
    }

    promedio = (float)sum / size;

    // Mostrar resultados
    printf("Suma: %d\n", sum);
    printf("Máximo: %d\n", max);
    printf("Mínimo: %d\n", min);
    printf("Promedio: %.2f\n", promedio);

    // Finalizar el tiempo y calcular la duración
    clock_t end_time = clock();  // Guardar el tiempo de finalización
    double time_taken = (double)(end_time - start_time) / CLOCKS_PER_SEC;  // Calcular el tiempo transcurrido

    // Mostrar el tiempo de ejecución
    printf("Tiempo de ejecución: %.6f segundos\n", time_taken);

    // Liberar memoria
    free(array);

    return 0;
}

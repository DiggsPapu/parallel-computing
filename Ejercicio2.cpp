#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <omp.h>
// Quicksort
void quicksort(int* array, int lo, int hi) {
    if (lo >= hi) return;
    int pivot = array[hi];
    int left = lo;
    int right = hi - 1;
    
    while (left <= right) {
        if (array[left] <= pivot) {
            left++;
        } else {
            std::swap(array[left], array[right]);
            right--;
        }
    }
    std::swap(array[left], array[hi]);

    #pragma omp task shared(array)
    quicksort(array, lo, left - 1);
    #pragma omp task shared(array)
    quicksort(array, left + 1, hi);
}

int main() {
    int N;
    std::cout << "Ingrese el número de elementos: ";
    std::cin >> N;

    // Generación de números aleatorios
    std::ofstream outFile("numeros.csv");
    std::srand(std::time(0));
    for (int i = 0; i < N; ++i) {
        int num = std::rand() % 1000;
        outFile << num;
        if (i < N - 1) outFile << ",";
    }
    outFile.close();

    // Lectura de números desde el archivo
    int* array = new int[N];
    std::ifstream inFile("numeros.csv");
    for (int i = 0; i < N; ++i) {
        inFile >> array[i];
        if (inFile.peek() == ',') inFile.ignore();
    }
    inFile.close();

    // Ordenamiento de números con QuickSort Paralelo
    double start_time = omp_get_wtime();
    #pragma omp parallel
    {
        #pragma omp single nowait
        quicksort(array, 0, N - 1);
    }
    double end_time = omp_get_wtime();
    std::cout << "Tiempo de ejecución paralelo: " << (end_time - start_time) << " segundos" << std::endl;

    // Escritura de números ordenados a un nuevo archivo
    std::ofstream sortedFile("numeros_ordenados.csv");
    for (int i = 0; i < N; ++i) {
        sortedFile << array[i];
        if (i < N - 1) sortedFile << ",";
    }
    sortedFile.close();

    // Liberar memoria
    delete[] array;

    return 0;
}

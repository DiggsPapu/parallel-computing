#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <chrono>  // Biblioteca para medir tiempo
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

// Main
int main() {
    int N;
    std::cout << "Ingrese el número de elementos: ";
    std::cin >> N;
    // Medir el tiempo de ordenamiento
    auto start = std::chrono::high_resolution_clock::now();
    
    // Generación de números aleatorios
    std::ofstream outFile("numeros.csv");
    std::srand(std::time(0));
    #pragma omp parallel for
    for (int i = 0; i < N; ++i) {
        int num = std::rand() % 1000;
        #pragma omp critical
        {
            outFile << num;
            if (i < N - 1) outFile << ",";
        }
    }
    outFile.close();

    // Lectura de números desde el archivo
    int* array = new int[N];
    std::ifstream inFile("numeros.csv");
    #pragma omp parallel for
    for (int i = 0; i < N; ++i) {
        inFile >> array[i];
        if (inFile.peek() == ',') inFile.ignore();
    }
    inFile.close();

    #pragma omp parallel
    {
        #pragma omp single nowait
        quicksort(array, 0, N - 1);
    }

    // Escritura de números ordenados a un nuevo archivo
    std::ofstream sortedFile("numeros_ordenados.csv");
    #pragma omp parallel for
    for (int i = 0; i < N; ++i) {
        #pragma omp critical
        {
            sortedFile << array[i];
            if (i < N - 1) sortedFile << ",";
        }
    }
    sortedFile.close();

    // Liberar memoria
    delete[] array;
    
    auto end = std::chrono::high_resolution_clock::now();
    // Calcular la duración en milisegundos
    std::chrono::duration<double, std::milli> duration = end - start;
    std::cout << "Tiempo del programa: " << duration.count() << " ms" << std::endl;
    return 0;
}

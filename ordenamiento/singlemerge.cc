#include <iostream>
#include <fstream>
#include <sstream>
#include <chrono>

// Función para mezclar dos subarrays ordenados
void merge(int* arr, int left, int mid, int right) {
    int n1 = mid - left + 1; // Tamaño del primer subarray
    int n2 = right - mid;    // Tamaño del segundo subarray

    // Crea arrays temporales para almacenar los datos
    int* L = new int[n1];
    int* R = new int[n2];

    // Copia los datos al subarray izquierdo y derecho
    for (int i = 0; i < n1; ++i)
        L[i] = arr[left + i];
    for (int j = 0; j < n2; ++j)
        R[j] = arr[mid + 1 + j];

    // Mezcla los dos subarrays de vuelta en el array original
    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            ++i;
        } else {
            arr[k] = R[j];
            ++j;
        }
        ++k;
    }

    // Copia los elementos restantes del subarray izquierdo, si hay
    while (i < n1) {
        arr[k] = L[i];
        ++i;
        ++k;
    }

    // Copia los elementos restantes del subarray derecho, si hay
    while (j < n2) {
        arr[k] = R[j];
        ++j;
        ++k;
    }

    // Libera la memoria de los arrays temporales
    delete[] L;
    delete[] R;
}

// Función recursiva de MergeSort
void mergeSort(int* arr, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2; // Encuentra el punto medio

        // Ordena recursivamente la primera mitad
        mergeSort(arr, left, mid);
        // Ordena recursivamente la segunda mitad
        mergeSort(arr, mid + 1, right);

        // Mezcla las dos mitades ordenadas
        merge(arr, left, mid, right);
    }
}

int main() {
    std::ifstream infile("random_array_1.txt"); // Abre el archivo de entrada, modificar nombre del archivo de texto a el dataset que se quiere probar
    std::ofstream outfile("sorted_dataset.txt");   // Abre el archivo de salida

    // Verifica si los archivos se abrieron correctamente
    if (!infile.is_open() || !outfile.is_open()) {
        std::cerr << "Error al abrir los archivos" << std::endl;
        return 1;
    }

    std::string line;
    const int MAX_SIZE = 10;  // Tamaño máximo del array, ajustar manualmente al tamaño del dataset seleccionado
    int arr[MAX_SIZE];        // Array estático para almacenar los datos

    // Lee una línea del archivo de entrada
    if (std::getline(infile, line)) {
        int size = 0;
        std::stringstream ss(line); // Convierte la línea en un stream

        // Lee los números de la línea y los almacena en el array
        while (ss >> arr[size]) {
            ++size;
        }

        // Mide el tiempo de ejecución del proceso de ordenación
        auto start = std::chrono::high_resolution_clock::now();

        // Llama a la función de MergeSort para ordenar el array
        mergeSort(arr, 0, size - 1);

        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> elapsed = end - start;

        // Escribe el array ordenado en el archivo de salida
        for (int i = 0; i < size; ++i) {
            outfile << arr[i] << " ";
        }
        outfile << std::endl;

        // Imprime el tiempo que tomó ordenar la lista
        std::cout << "Tiempo de ordenación: " << elapsed.count() << " segundos" << std::endl;
    } else {
        std::cerr << "No se pudo leer la lista del archivo" << std::endl;
    }

    // Cierra los archivos de entrada y salida
    infile.close();
    outfile.close();
    return 0;
}

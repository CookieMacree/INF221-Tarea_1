#include <iostream>
#include <fstream>
#include <sstream>
#include <chrono>

// Función para intercambiar dos elementos
void swap(int* a, int* b) {
    int t = *a;
    *a = *b;
    *b = t;
}

// Función para particionar el array
int partition(int* arr, int low, int high) {
    int pivot = arr[high]; // Se toma el último elemento como pivote
    int i = (low - 1);     // Índice del elemento más pequeño

    // Recorre el array y compara con el pivote
    for (int j = low; j <= high - 1; j++) {
        if (arr[j] <= pivot) { // Si el elemento es menor o igual al pivote
            i++;
            swap(&arr[i], &arr[j]); // Se intercambia con el elemento más pequeño
        }
    }
    swap(&arr[i + 1], &arr[high]); // Se coloca el pivote en su posición correcta
    return (i + 1); // Devuelve la posición del pivote
}

// Función QuickSort que ordena el array recursivamente
void quickSort(int* arr, int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high); // Obtiene la posición del pivote
        quickSort(arr, low, pi - 1);        // Ordena los elementos antes del pivote
        quickSort(arr, pi + 1, high);       // Ordena los elementos después del pivote
    }
}

int main() {
    std::ifstream infile("random_array_1.txt"); // Abre el archivo de entrada, modificar nombre del archivo de texto a el dataset que se quiere probar
    std::ofstream outfile("sorted_dataset.txt");  // Abre el archivo de salida

    // Verifica si los archivos se abrieron correctamente
    if (!infile.is_open() || !outfile.is_open()) {
        std::cerr << "Error al abrir los archivos" << std::endl;
        return 1;
    }

    std::string line;
    const int MAX_SIZE = 10; // Tamaño máximo del array, ajustar manualmente al tamaño del dataset seleccionado
    int arr[MAX_SIZE];            // Array para almacenar los datos

    // Lee una línea del archivo de entrada
    if (std::getline(infile, line)) {
        int size = 0;
        std::stringstream ss(line); // Convierte la línea en un stream

        // Lee los números de la línea y los almacena en el array
        while (ss >> arr[size]) {
            ++size;
        }

        // Mide el tiempo de ejecución de la ordenación
        auto start = std::chrono::high_resolution_clock::now();

        // Llama a la función de ordenación QuickSort
        quickSort(arr, 0, size - 1);

        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> elapsed = end - start;

        // Escribe el array ordenado en el archivo de salida
        for (int i = 0; i < size; ++i) {
            outfile << arr[i] << " ";
        }
        outfile << std::endl;

        // Imprime el tiempo tomado para ordenar
        std::cout << "Tiempo de ordenación: " << elapsed.count() << " segundos" << std::endl;
    } else {
        std::cerr << "No se pudo leer la lista del archivo" << std::endl;
    }

    // Cierra los archivos
    infile.close();
    outfile.close();
    return 0;
}

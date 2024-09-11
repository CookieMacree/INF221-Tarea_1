#include <iostream>
#include <fstream>
#include <sstream>
#include <chrono>

// Función para ordenar un array usando Insertion Sort
void insertionSort(int* arr, int n) {
    for (int i = 1; i < n; ++i) {
        int key = arr[i]; // selecciona el elemento actual
        int j = i - 1;

        // Mueve los elementos que son mayores que 'key' a una posición adelante
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j]; // Desplaza el elemento hacia la derecha
            --j;
        }
        arr[j + 1] = key; // Coloca 'key' en su posición correcta
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
    int arr[MAX_SIZE];        // Array para almacenar los datos

    // Lee una línea del archivo de entrada
    if (std::getline(infile, line)) {
        int size = 0;
        std::stringstream ss(line); // Convierte la línea en un stream

        // Lee los números de la línea y los almacena en el array
        while (ss >> arr[size]) {
            ++size; // Incrementa el tamaño del array
        }

        // Mide el tiempo de ejecución de la ordenación
        auto start = std::chrono::high_resolution_clock::now();

        // Llama a la función de ordenación (Insertion Sort)
        insertionSort(arr, size);

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

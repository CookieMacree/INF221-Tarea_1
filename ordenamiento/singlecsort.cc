#include <iostream>
#include <fstream>
#include <sstream>
#include <chrono>
#include <algorithm> // Incluye std::sort

int main() {
    std::ifstream infile("random_array_1.txt"); // Abre el archivo de entrada, modificar nombre del archivo de texto a el dataset que se quiere probar
    std::ofstream outfile("sorted_dataset.txt");   // Abre el archivo de salida

    // Verifica si los archivos fueron abiertos correctamente
    if (!infile.is_open() || !outfile.is_open()) {
        std::cerr << "Error al abrir los archivos" << std::endl;
        return 1;
    }

    std::string line;
    const int MAX_SIZE = 10;  // Tamaño máximo del array, ajustar manualmente al tamaño del dataset seleccionado
    int* arr = new int[MAX_SIZE];  // Array dinámico para almacenar los datos

    // Se espera solo una línea con la lista en el archivo
    if (std::getline(infile, line)) {
        int size = 0;
        std::stringstream ss(line);  // Convierte la línea en un stream

        // Lee los números de la línea y los almacena en el array
        while (ss >> arr[size]) {
            ++size;
        }

        // Mide el tiempo de ordenación usando std::sort
        auto start = std::chrono::high_resolution_clock::now();

        // Ordena el array con std::sort
        std::sort(arr, arr + size);

        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> elapsed = end - start;

        // Escribe el array ordenado en el archivo de salida
        for (int i = 0; i < size; ++i) {
            outfile << arr[i] << " ";
        }
        outfile << std::endl;

        // Imprime el tiempo que tomó ordenar el array
        std::cout << "Tiempo de ordenación: " << elapsed.count() << " segundos" << std::endl;
    } else {
        std::cerr << "No se pudo leer la lista del archivo" << std::endl;
    }

    delete[] arr;  // Libera la memoria dinámica asignada al array
    infile.close();
    outfile.close();
    return 0;
}

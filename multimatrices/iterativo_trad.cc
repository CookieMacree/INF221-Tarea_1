#include <iostream>
#include <fstream>
#include <chrono>

// Función para multiplicar dos matrices A y B, y almacenar el resultado en C
void multiplicarMatrices(int** A, int** B, int** C, int n) {
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            C[i][j] = 0;
            for (int k = 0; k < n; ++k) {
                C[i][j] += A[i][k] * B[k][j];  // Suma de productos
            }
        }
    }
}

int main() {
    // Abrir archivos de entrada y salida
    std::ifstream infileA("triangular_superior_matriz_1.txt"); //modificar nombre del archivo de texto a el dataset que se quiere probar
    std::ifstream infileB("triangular_superior_matriz_2.txt");
    std::ofstream outfile("resultado_matriz.txt");

    if (!infileA.is_open() || !infileB.is_open() || !outfile.is_open()) {
        std::cerr << "Error al abrir los archivos" << std::endl;
        return 1;
    }

    int n;  // Tamaño de las matrices (se asume que son cuadradas)
    
    // Leer el tamaño de las matrices desde los archivos
    infileA >> n;
    infileB >> n;

    // Reservar memoria para las matrices
    int** A = new int*[n];
    int** B = new int*[n];
    int** C = new int*[n];
    for (int i = 0; i < n; ++i) {
        A[i] = new int[n];
        B[i] = new int[n];
        C[i] = new int[n];
    }

    // Leer las matrices desde los archivos
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            infileA >> A[i][j];
            infileB >> B[i][j];
        }
    }

    // Medir el tiempo de multiplicación
    auto start_total = std::chrono::high_resolution_clock::now();

    // Multiplicar las matrices
    multiplicarMatrices(A, B, C, n);

    auto end_total = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed_total = end_total - start_total;

    std::cout << "Tiempo total de multiplicación: " << elapsed_total.count() << " segundos" << std::endl;

    // Escribir la matriz resultante en el archivo de salida
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            outfile << C[i][j] << " ";
        }
        outfile << std::endl;
    }

    // Liberar la memoria asignada a las matrices
    for (int i = 0; i < n; ++i) {
        delete[] A[i];
        delete[] B[i];
        delete[] C[i];
    }
    delete[] A;
    delete[] B;
    delete[] C;

    infileA.close();
    infileB.close();
    outfile.close();

    return 0;
}

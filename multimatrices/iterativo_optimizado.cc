#include <iostream>
#include <fstream>
#include <chrono>

// Función para transponer la matriz B
void transponerMatriz(int** B, int** B_T, int n) {
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            B_T[j][i] = B[i][j];  // Transpone B y la guarda en B_T
        }
    }
}

// Función para multiplicar las matrices A y B_T
void multiplicarMatricesOptimizado(int** A, int** B_T, int** C, int n) {
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            C[i][j] = 0;
            for (int k = 0; k < n; ++k) {
                C[i][j] += A[i][k] * B_T[j][k];  // Accede a B_T por filas
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
    int** B_T = new int*[n];  // Matriz transpuesta de B
    int** C = new int*[n];

    for (int i = 0; i < n; ++i) {
        A[i] = new int[n];
        B[i] = new int[n];
        B_T[i] = new int[n];  // Reserva para la transpuesta de B
        C[i] = new int[n];
    }

    // Leer las matrices desde los archivos
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            infileA >> A[i][j];
            infileB >> B[i][j];
        }
    }

    // Transponer la matriz B para mejorar la localidad de los datos
    transponerMatriz(B, B_T, n);

    // Medir el tiempo de multiplicación
    auto start_total = std::chrono::high_resolution_clock::now();

    // Multiplicar las matrices (A * B_T)
    multiplicarMatricesOptimizado(A, B_T, C, n);

    auto end_total = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed_total = end_total - start_total;

    std::cout << "Tiempo total de multiplicación (optimizado): " << elapsed_total.count() << " segundos" << std::endl;

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
        delete[] B_T[i];  // Liberar la memoria de la transpuesta
        delete[] C[i];
    }
    delete[] A;
    delete[] B;
    delete[] B_T;
    delete[] C;

    infileA.close();
    infileB.close();
    outfile.close();

    return 0;
}

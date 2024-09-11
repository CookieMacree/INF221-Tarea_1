#include <iostream>
#include <fstream>
#include <chrono>
#include <cmath>

// Función para crear una matriz de tamaño n x n
int** createMatrix(int n) {
    int** mat = new int*[n];
    for (int i = 0; i < n; ++i)
        mat[i] = new int[n](); // Inicializa todas las entradas en 0
    return mat;
}

// Función para liberar la memoria de una matriz
void deleteMatrix(int** mat, int n) {
    for (int i = 0; i < n; ++i)
        delete[] mat[i]; // Libera cada fila
    delete[] mat; // Libera el puntero de las filas
}

// Función para sumar dos matrices
void sumMatrices(int** A, int** B, int** C, int n) {
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            C[i][j] = A[i][j] + B[i][j]; // Suma elemento a elemento
}

// Función para restar dos matrices
void subtractMatrices(int** A, int** B, int** C, int n) {
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            C[i][j] = A[i][j] - B[i][j]; // Resta elemento a elemento
}

// Función para multiplicar matrices utilizando el algoritmo tradicional
void traditionalMultiply(int** A, int** B, int** C, int n) {
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            for (int k = 0; k < n; ++k)
                C[i][j] += A[i][k] * B[k][j]; // Multiplicación tradicional
}

// Función para multiplicar matrices usando el algoritmo de Strassen
void strassenMultiply(int** A, int** B, int** C, int n) {
    // Caso base para matrices pequeñas (2x2 o menores)
    if (n <= 2) {
        traditionalMultiply(A, B, C, n);
        return;
    }

    int newSize = n / 2; // Tamaño de las submatrices

    // Crear submatrices de tamaño newSize x newSize
    int** A11 = createMatrix(newSize);
    int** A12 = createMatrix(newSize);
    int** A21 = createMatrix(newSize);
    int** A22 = createMatrix(newSize);
    int** B11 = createMatrix(newSize);
    int** B12 = createMatrix(newSize);
    int** B21 = createMatrix(newSize);
    int** B22 = createMatrix(newSize);
    int** C11 = createMatrix(newSize);
    int** C12 = createMatrix(newSize);
    int** C21 = createMatrix(newSize);
    int** C22 = createMatrix(newSize);
    int** M1 = createMatrix(newSize);
    int** M2 = createMatrix(newSize);
    int** M3 = createMatrix(newSize);
    int** M4 = createMatrix(newSize);
    int** M5 = createMatrix(newSize);
    int** M6 = createMatrix(newSize);
    int** M7 = createMatrix(newSize);
    int** AResult = createMatrix(newSize);
    int** BResult = createMatrix(newSize);

    // Dividir las matrices A y B en 4 submatrices cada una
    for (int i = 0; i < newSize; ++i) {
        for (int j = 0; j < newSize; ++j) {
            A11[i][j] = A[i][j];
            A12[i][j] = A[i][j + newSize];
            A21[i][j] = A[i + newSize][j];
            A22[i][j] = A[i + newSize][j + newSize];
            B11[i][j] = B[i][j];
            B12[i][j] = B[i][j + newSize];
            B21[i][j] = B[i + newSize][j];
            B22[i][j] = B[i + newSize][j + newSize];
        }
    }

    // Calcular los productos M1 a M7
    sumMatrices(A11, A22, AResult, newSize);
    sumMatrices(B11, B22, BResult, newSize);
    strassenMultiply(AResult, BResult, M1, newSize);

    sumMatrices(A21, A22, AResult, newSize);
    strassenMultiply(AResult, B11, M2, newSize);

    subtractMatrices(B12, B22, BResult, newSize);
    strassenMultiply(A11, BResult, M3, newSize);

    subtractMatrices(B21, B11, BResult, newSize);
    strassenMultiply(A22, BResult, M4, newSize);

    sumMatrices(A11, A12, AResult, newSize);
    strassenMultiply(AResult, B22, M5, newSize);

    subtractMatrices(A21, A11, AResult, newSize);
    sumMatrices(B11, B12, BResult, newSize);
    strassenMultiply(AResult, BResult, M6, newSize);

    subtractMatrices(A12, A22, AResult, newSize);
    sumMatrices(B21, B22, BResult, newSize);
    strassenMultiply(AResult, BResult, M7, newSize);

    // Combinar los resultados de M1 a M7 en la matriz C
    sumMatrices(M1, M4, AResult, newSize);
    subtractMatrices(AResult, M5, BResult, newSize);
    sumMatrices(BResult, M7, C11, newSize);

    sumMatrices(M3, M5, C12, newSize);

    sumMatrices(M2, M4, C21, newSize);

    subtractMatrices(M1, M2, AResult, newSize);
    sumMatrices(AResult, M3, BResult, newSize);
    sumMatrices(BResult, M6, C22, newSize);

    // Reconstruir la matriz C a partir de las submatrices C11, C12, C21 y C22
    for (int i = 0; i < newSize; ++i) {
        for (int j = 0; j < newSize; ++j) {
            C[i][j] = C11[i][j];
            C[i][j + newSize] = C12[i][j];
            C[i + newSize][j] = C21[i][j];
            C[i + newSize][j + newSize] = C22[i][j];
        }
    }

    // Liberar la memoria de las submatrices y matrices intermedias
    deleteMatrix(A11, newSize);
    deleteMatrix(A12, newSize);
    deleteMatrix(A21, newSize);
    deleteMatrix(A22, newSize);
    deleteMatrix(B11, newSize);
    deleteMatrix(B12, newSize);
    deleteMatrix(B21, newSize);
    deleteMatrix(B22, newSize);
    deleteMatrix(C11, newSize);
    deleteMatrix(C12, newSize);
    deleteMatrix(C21, newSize);
    deleteMatrix(C22, newSize);
    deleteMatrix(M1, newSize);
    deleteMatrix(M2, newSize);
    deleteMatrix(M3, newSize);
    deleteMatrix(M4, newSize);
    deleteMatrix(M5, newSize);
    deleteMatrix(M6, newSize);
    deleteMatrix(M7, newSize);
    deleteMatrix(AResult, newSize);
    deleteMatrix(BResult, newSize);
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

    int n;
    infileA >> n;
    infileB >> n;

    int** A = createMatrix(n);
    int** B = createMatrix(n);
    int** C = createMatrix(n);

    // Leer las matrices desde los archivos
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            infileA >> A[i][j];
            infileB >> B[i][j];
        }
    }

    // Medir el tiempo de ejecución de la multiplicación
    auto start_total = std::chrono::high_resolution_clock::now();

    strassenMultiply(A, B, C, n);

    auto end_total = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed_total = end_total - start_total;

    std::cout << "Tiempo total de multiplicación (Strassen): " << elapsed_total.count() << " segundos" << std::endl;

    // Guardar el resultado en un archivo
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            outfile << C[i][j] << " ";
        }
        outfile << std::endl;
    }

    // Liberar la memoria
    deleteMatrix(A, n);
    deleteMatrix(B, n);
    deleteMatrix(C, n);

    infileA.close();
    infileB.close();
    outfile.close();

    return 0;
}

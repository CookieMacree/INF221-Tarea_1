import numpy as np

# Variables globales
TAMANO_MATRIZ = 2          # Tamaño de las matrices (se puede ajustar)
VALOR_MIN = 0               # Límite inferior del rango para valores aleatorios
VALOR_MAX = 1000            # Límite superior del rango para valores aleatorios

# Funciones para generar matrices de diferentes tipos
def generar_matriz_random():
    # Genera una matriz con valores aleatorios
    return np.random.randint(VALOR_MIN, VALOR_MAX, (TAMANO_MATRIZ, TAMANO_MATRIZ))

def generar_matriz_nula():
    # Genera una matriz de ceros
    return np.zeros((TAMANO_MATRIZ, TAMANO_MATRIZ), dtype=int)

def generar_matriz_simetrica():
    # Genera una matriz simétrica
    matriz = np.random.randint(VALOR_MIN, VALOR_MAX, (TAMANO_MATRIZ, TAMANO_MATRIZ))
    return (matriz + matriz.T) // 2

def generar_matriz_triangular_superior():
    # Genera una matriz triangular superior
    return np.triu(np.random.randint(VALOR_MIN, VALOR_MAX, (TAMANO_MATRIZ, TAMANO_MATRIZ)))

# Función para guardar la matriz en un archivo de texto
def guardar_matriz_en_txt(matriz, nombre_archivo):
    with open(nombre_archivo, 'w') as f:
        f.write(f"{TAMANO_MATRIZ}\n")  # Escribe el tamaño de la matriz
        np.savetxt(f, matriz, fmt='%d')  # Guarda la matriz en el archivo

# Generación y guardado de matrices
matrices_generadores = {
    "random": generar_matriz_random,
    "nula": generar_matriz_nula,
    "simetrica": generar_matriz_simetrica,
    "triangular_superior": generar_matriz_triangular_superior,
}

for nombre, generador in matrices_generadores.items():
    matriz_1 = generador()  # Genera la primera matriz
    matriz_2 = generador()  # Genera la segunda matriz
    guardar_matriz_en_txt(matriz_1, f'{nombre}_matriz_1.txt')  # Guarda la primera matriz
    guardar_matriz_en_txt(matriz_2, f'{nombre}_matriz_2.txt')  # Guarda la segunda matriz

print(f"Dos matrices de cada categoría de tamaño {TAMANO_MATRIZ}x{TAMANO_MATRIZ} han sido generadas y guardadas en archivos de texto separados.")

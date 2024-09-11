import random

# Función para generar arrays de diferentes tipos
def generar_array(tamaño_array, tipo="random"):
    if tipo == "random":
        # Genera un array con números aleatorios
        array = [random.randint(0, 1000000) for _ in range(tamaño_array)]
    elif tipo == "ordenada":
        # Genera un array ordenado
        array = sorted(random.randint(0, 1000000) for _ in range(tamaño_array))
    elif tipo == "inversa":
        # Genera un array ordenado en orden inverso
        array = sorted((random.randint(0, 1000000) for _ in range(tamaño_array)), reverse=True)
    elif tipo == "casi_ordenada":
        # Genera un array ordenado con algunos intercambios aleatorios
        array = sorted(random.randint(0, 1000000) for _ in range(tamaño_array))
        for _ in range(tamaño_array // 10):
            i, j = random.sample(range(tamaño_array), 2)
            array[i], array[j] = array[j], array[i]
    return array

# Función para guardar el array en un archivo de texto
def guardar_array_en_txt(array, nombre_archivo):
    with open(nombre_archivo, 'w') as archivo:
        archivo.write(' '.join(map(str, array)) + '\n')

# Parámetros para generar arrays
cantidad_arrays = 1    # Número de arrays por tipo, modificar para generar mas datasets
tamaño_array = 10      # Tamaño de cada array, modificar para cambiar tamaño de la lista

# Tipos de arrays a generar
tipos = ["random", "ordenada", "inversa", "casi_ordenada"]

# Generar y guardar los arrays en archivos
for tipo in tipos:
    for i in range(cantidad_arrays):
        array = generar_array(tamaño_array, tipo=tipo)
        guardar_array_en_txt(array, f'{tipo}_array_{i+1}.txt')

print(f"Se generaron {cantidad_arrays} arrays de cada tipo y se guardaron en archivos de texto separados.")

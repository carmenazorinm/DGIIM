import os

# Ruta de la carpeta que contiene los archivos
carpeta = '/home/carmenc/Universidad/Erasmus/DeepLearning/Datasets/test_data/images'

# Obtener nombres de archivos en la carpeta
nombres_archivos = sorted(os.listdir(carpeta))

# Ruta del archivo de texto para escribir los nombres
archivo_txt = '/home/carmenc/Universidad/Erasmus/DeepLearning/Datasets/test_data/more_words.txt'

# Escribir los nombres de archivos en el archivo de texto
with open(archivo_txt, 'w') as file:
    for nombre_archivo in nombres_archivos:
        file.write(nombre_archivo + '\n')

print(f'Se han guardado los nombres de archivos en {archivo_txt}')

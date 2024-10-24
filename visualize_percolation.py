import numpy as np
import pandas as pd
import matplotlib.pyplot as plt
import random
import matplotlib.colors as mcolors
import time
import os

def assign_random_colors(num_nodes):
    # Genera un color RGB aleatorio para cada nodo
    return {node: (random.random(), random.random(), random.random()) for node in range(num_nodes)}

def plot_percolation_state(grid_size, node_clusters, p_value, ax, color_map):
    # Creamos una matriz de tamaño grid_size x grid_size que representa el estado de la red
    grid = np.array(node_clusters).reshape((grid_size, grid_size))

    # Limpiamos la gráfica antes de dibujar la nueva
    ax.clear()

    # Creamos una nueva matriz de colores basada en el clúster al que pertenece cada nodo
    colored_grid = np.zeros((grid_size, grid_size, 3))  # 3 canales RGB

    for i in range(grid_size):
        for j in range(grid_size):
            cluster_id = grid[i, j]
            colored_grid[i, j] = color_map[cluster_id]  # Asignamos el color del clúster

    # Dibujar la cuadrícula de nodos coloreados
    ax.imshow(colored_grid)

    # Actualizar el título
    ax.set_title(f"Estado de la percolación - p = {p_value:.2f}")
    ax.set_xticks([])  # Eliminamos los ejes x
    ax.set_yticks([])  # Eliminamos los ejes y

def visualize_percolation(csv_file, grid_size, delay=1, save_images=False):
    # Leer el archivo CSV
    df = pd.read_csv(csv_file)

    # Asignar colores aleatorios únicos a cada nodo inicialmente
    num_nodes = grid_size * grid_size
    color_map = assign_random_colors(num_nodes)

    # Inicializar el gráfico
    fig, ax = plt.subplots(figsize=(8, 8))

    # Iteramos sobre cada fila, que corresponde a un valor de p
    for index, row in df.iterrows():
        p_value = row[0]  # Primer valor es p
        node_clusters = row[1:].values.astype(int)  # El resto son los clústeres de cada nodo

        # Dibujar el estado actual de la percolación
        plot_percolation_state(grid_size, node_clusters, p_value, ax, color_map)

        # Mostrar o guardar las imágenes
        if save_images:
            plt.savefig(f"percolation_images/percolation_p_{p_value:.2f}.png")

        # Hacer una pausa para actualizar la visualización
        plt.pause(delay)

    plt.show()


if __name__ == "__main__":
    csv_file = "cluster_of_each_node.csv"  # Archivo de entrada
    grid_size = 500  # Tamaño de la cuadrícula (ejemplo: 10x10)
    delay = 1  # Retraso de 1 segundo entre cada imagen
    save_images = False  # Cambia a True si quieres guardar las imágenes

    # Crear la carpeta para guardar las imágenes si es necesario
    if save_images and not os.path.exists("percolation_images"):
        os.makedirs("percolation_images")

    # Ejecutar la visualización
    visualize_percolation(csv_file, grid_size, delay, save_images)

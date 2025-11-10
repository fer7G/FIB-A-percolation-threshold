import numpy as np
import pandas as pd
import matplotlib.pyplot as plt
import random
import os
from PIL import Image

def assign_random_colors(num_nodes):
    return {node: (random.random(), random.random(), random.random()) for node in range(num_nodes)}

def plot_percolation_state(grid_size, node_clusters, p_value, ax, color_map):
    grid = np.array(node_clusters).reshape((grid_size, grid_size))
    ax.clear()
    colored_grid = np.zeros((grid_size, grid_size, 3))

    for i in range(grid_size):
        for j in range(grid_size):
            cluster_id = grid[i, j]
            colored_grid[i, j] = color_map[cluster_id]

    ax.imshow(colored_grid, interpolation='none')  # Use 'nearest' interpolation for sharper images
    ax.set_title(f"Percolation state - p = {p_value:.2f}")
    ax.set_xticks([])
    ax.set_yticks([])

def visualize_percolation(csv_file, grid_size, save_gif=False, gif_name="percolation.gif", duration=0.5):
    df = pd.read_csv(csv_file)
    num_nodes = grid_size * grid_size
    color_map = assign_random_colors(num_nodes)

    images = []
    fig, ax = plt.subplots(figsize=(6, 6))

    temp_dir = "../data/percolation_images"
    if save_gif and not os.path.exists(temp_dir):
        os.makedirs(temp_dir)

    for index, row in df.iterrows():
        p_value = row[0]
        node_clusters = row[1:].values.astype(int)

        plot_percolation_state(grid_size, node_clusters, p_value, ax, color_map)

        # Guardar la imagen temporal
        if save_gif:
            img_path = f"{temp_dir}/frame_{index:03d}.png"
            plt.savefig(img_path)
            images.append(Image.open(img_path))

        else:
            plt.pause(duration)

    if save_gif:
        gif_path = f"../data/{gif_name}"
        images[0].save(gif_path, save_all=True, append_images=images[1:], duration=int(duration * 1000), loop=0)
        print(f"GIF saved to: {gif_path}")
    else:
        plt.show()

if __name__ == "__main__":
    csv_file = "../data/cluster_of_each_node.csv"
    grid_size = 500
    save_gif = True  # Cambia a True para crear el GIF
    duration = 0.1   # Duración (s) entre frames del GIF

    visualize_percolation(csv_file, grid_size, save_gif=save_gif, duration=duration)

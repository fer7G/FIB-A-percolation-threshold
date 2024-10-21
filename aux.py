import subprocess
import pandas as pd
import matplotlib.pyplot as plt
import os
import numpy as np  #

def plot_results(filenames, output_photo_base, colors):
    # Initialize a new figure
    plt.figure(figsize=(10, 6))

    for i, filename in enumerate(filenames):
        df = pd.read_csv(filename)

        # Plot q values vs. number of connected components
        plt.plot(df["q"], df["Componentes Conexos"], marker="o", linestyle="-", color=colors[i % len(colors)], 
                 label=f"Componentes Conexos - {os.path.basename(filename)}", markersize=2)

    plt.xlabel("Probabilidad de Percolación (q)")
    plt.ylabel("Número de Componentes Conexos")
    plt.title("Componentes Conexos vs Probabilidad de Percolación")
    plt.legend()
    plt.grid()
    plt.savefig(f'{output_photo_base}_componentes_conexos.png')  # Save plot
    plt.close()  # Close the figure to avoid overlapping

    # Similar plotting for Tamaño Clúster Mayor
    plt.figure(figsize=(10, 6))
    for i, filename in enumerate(filenames):
        df = pd.read_csv(filename)
        plt.plot(df["q"], df["Tamaño Clúster Mayor"], marker="o", linestyle="-", color=colors[i % len(colors)], 
                 label=f"Tamaño Clúster Mayor - {os.path.basename(filename)}", markersize=2)

    plt.xlabel("Probabilidad de Percolación (q)")
    plt.ylabel("Tamaño Clúster Mayor")
    plt.title("Tamaño Clúster Mayor vs Probabilidad de Percolación")
    plt.legend()
    plt.grid()
    plt.savefig(f'{output_photo_base}_cluster_mayor.png')  # Save plot
    plt.close()

    # Similar plotting for N_sc
    plt.figure(figsize=(10, 6))
    for i, filename in enumerate(filenames):
        df = pd.read_csv(filename)
        plt.plot(df["q"], df["N_sc"], marker="o", linestyle="-", color=colors[i % len(colors)], 
                 label=f"N_sc - {os.path.basename(filename)}", markersize=2)

    plt.xlabel("Probabilidad de Percolación (q)")
    plt.ylabel("N_sc")
    plt.title("N_sc vs Probabilidad de Percolación")
    plt.legend()
    plt.grid()
    plt.savefig(f'{output_photo_base}_n_sc.png')  # Save plot
    plt.close()


csv_filenames = ["N=50.csv","N=100.csv","N=200.csv","N=500.csv","N=800.csv","N=1000.csv" ]
output_photo_base = "resultados_malla_aristas"
colors = ['r', 'g', 'b', 'c', 'm', 'y', 'k']  # Extend this list if you have more DIMACS files

plot_results(csv_filenames, output_photo_base, colors)

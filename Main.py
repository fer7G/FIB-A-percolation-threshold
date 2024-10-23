import subprocess
import pandas as pd
import matplotlib.pyplot as plt
import os
import numpy as np  # For NaN handling
import graph_generator as gg
import calculateBeta as cb

def run_percolation_program(executable, dimacs_file, percolation_type, step):
    # Run the C++ program and capture the output
    result = subprocess.run(
        [executable],
        input=f"{dimacs_file}\n{percolation_type}\n{step}\n",
        text=True,
        capture_output=True
    )
    print(result.stdout)

    # Check for errors
    if result.returncode != 0:
        print("Error running the program:", result.stderr)
        return None, None

    # Parse output to retrieve results
    results = []
    percolationThreshold = None
    for line in result.stdout.splitlines():
        if line.startswith("q ="):
            # Extract values of q, Componentes Conexos, Tamaño Clúster Mayor, and N_sc
            parts = line.split(", ")
            q_value = float(parts[0].split("= ")[1])
            num_components = int(parts[1])
            cluster_size = int(parts[2])
            N_sc = float(parts[3])
            results.append((q_value, num_components, cluster_size, N_sc))

        elif line.startswith("Percolación detectada a q = "):
            percolationThreshold = float(line.split("= ")[1])
            print(percolationThreshold)

    return results, percolationThreshold

def save_results_to_csv(results, filename, percolThresh):
    # Create DataFrame with new columns
    df_cols = pd.DataFrame(results, columns=['q', 'Componentes Conexos', 'Tamaño Clúster Mayor', 'N_sc'])

    # Insert a row of NaNs to separate different executions
    separator = pd.DataFrame([[np.nan] * 4], columns=['q', 'Componentes Conexos', 'Tamaño Clúster Mayor', 'N_sc'])
    
    if os.path.exists(filename):
        df_existente = pd.read_csv(filename)
        # Append new data with NaN separator
        df_total = pd.concat([df_existente, separator, df_cols], ignore_index=True)
    else:
        df_total = df_cols

    # Save the updated file in CSV format
    df_total.to_csv(filename, index=False)
    print("Resultados acumulados guardados en ", filename)

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

# Parameters for the program execution
# Parameters for the program execution
def save_averaged_results_to_csv(results_list, filename, percolThresh):
    # Create a dictionary to accumulate sums and counts for averaging
    avg_results = {}
    
    for results in results_list:
        if results:  # Check if the results are not empty
            for q_value, num_components, cluster_size, N_sc in results:
                if q_value not in avg_results:
                    avg_results[q_value] = [0, 0, 0, 0]  # [sum_num_components, sum_cluster_size, sum_N_sc, count]
                
                avg_results[q_value][0] += num_components
                avg_results[q_value][1] += cluster_size
                avg_results[q_value][2] += N_sc
                avg_results[q_value][3] += 1  # Increment the count
    
    # Calculate average values
    averaged_data = []
    for q_value, (sum_num_components, sum_cluster_size, sum_N_sc, count) in avg_results.items():
        averaged_data.append((q_value, 
                              sum_num_components / count, 
                              sum_cluster_size / count, 
                              sum_N_sc / count))
    
    avg_df = pd.DataFrame(averaged_data, columns=['q', 'Componentes Conexos', 'Tamaño Clúster Mayor', 'N_sc'])

    # Insert a row of NaNs to separate different executions
    separator = pd.DataFrame([[np.nan] * 4], columns=['q', 'Componentes Conexos', 'Tamaño Clúster Mayor', 'N_sc'])
    
    if os.path.exists(filename):
        df_existente = pd.read_csv(filename)
        # Append new average data with NaN separator
        df_total = pd.concat([df_existente, separator, avg_df], ignore_index=True)
    else:
        df_total = avg_df

    # Save the updated file in CSV format
    df_total.to_csv(filename, index=False)
    print("Average resultados acumulados guardados en ", filename)

# Parameters for the program execution

executable = "./programa"  # Update with the path to your executable

generate_graph = input("Quieres generar un grafo? (y/n): \n")
if generate_graph == "y":
    gg.main()


percolation_type = input("Quieres hacer percolación por aristas(1) o nodos(2): \n")  # 1 for Bond Percolation, 2 for Site Percolation
step = input("Introduce el step: \n")
output_photo_base = input("Introduce el nombre para las fotos resultantes(sin extension .png): \n")
csv_file = input("Introduce el nombre del archivo csv (Sin extensión .csv): \n")
iterations = int(input("Cuantas iteraciones quieres hacer?: \n"))

# User input for DIMACS files
dimacs_files_input = input("Introduce los archivos DIMACS separados por comas: \n")
dimacs_files = [file.strip() for file in dimacs_files_input.split(",")]

# Define a color palette
colors = ['r', 'g', 'b', 'c', 'm', 'y', 'k']  # Extend this list if you have more DIMACS files

# Store the CSV filenames for each DIMACS file
csv_filenames = []

for dimacs_file in dimacs_files:
    print(f"Running experiments for {dimacs_file}")
    
    results_list = []  # To store results for each iteration for averaging

    for i in range(1, iterations + 1):
        print(f"Running execution: {i} for {dimacs_file}")
        results, percolationThreshold = run_percolation_program(executable, dimacs_file, percolation_type, step)
        if results:
            results_list.append(results)  # Collect results for averaging

    # Save averaged results to CSV after all iterations for the current graph size
    save_averaged_results_to_csv(results_list, f"{csv_file}_{os.path.basename(dimacs_file)}.csv", percolationThreshold)
    csv_filenames.append(f"{csv_file}_{os.path.basename(dimacs_file)}.csv")  # Collect CSV filenames

# Plot the results from all CSV files
plot_results(csv_filenames, output_photo_base, colors)


    
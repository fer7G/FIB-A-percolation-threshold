import subprocess
import pandas as pd
import matplotlib.pyplot as plt
import os

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
        return None

    # Parse output to retrieve results
    results = []
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

def save_results_to_excel(results, filename, percolThresh):
    # Create DataFrame with new columns
    df_cols = pd.DataFrame(results, columns=['q', 'Componentes Conexos', 'Tamaño Clúster Mayor', 'N_sc'])
    df_espacio = pd.DataFrame(columns=['q', 'Componentes Conexos', 'Tamaño Clúster Mayor', 'N_sc'], index=[-1])  # Space separator
    df_percolThresh = pd.DataFrame({'Umbral de Percolación': [percolThresh]})

    if os.path.exists(filename):
        df_existente = pd.read_excel(filename)
        df_total = pd.concat([df_existente, df_espacio, df_cols, df_percolThresh], ignore_index=False)
    else:
        df_total = df_cols

    # Save the updated file
    df_total.to_excel(filename, index=False)
    print("Resultados acumulados guardados en ", filename)

def plot_results(filename, output_photo_base):
    # Load the Excel file
    df = pd.read_excel(filename)

    # Plot q values vs. number of connected components
    plt.figure(figsize=(10, 6))
    plt.plot(df["q"], df["Componentes Conexos"], marker="o", linestyle="-", color="b", label="Componentes Conexos")
    plt.xlabel("Probabilidad de Percolación (q)")
    plt.ylabel("Número de Componentes Conexos")
    plt.title("Componentes Conexos vs Probabilidad de Percolación")
    plt.legend()
    plt.grid()
    plt.savefig(f'{output_photo_base}_componentes_conexos.png')  # Save plot
    plt.show()

    # Plot q values vs Tamaño Clúster Mayor
    plt.figure(figsize=(10, 6))
    plt.plot(df["q"], df["Tamaño Clúster Mayor"], marker="o", linestyle="-", color="r", label="Tamaño Clúster Mayor")
    plt.xlabel("Probabilidad de Percolación (q)")
    plt.ylabel("Tamaño Clúster Mayor")
    plt.title("Tamaño Clúster Mayor vs Probabilidad de Percolación")
    plt.legend()
    plt.grid()
    plt.savefig(f'{output_photo_base}_cluster_mayor.png')  # Save plot
    plt.show()

    # Plot q values vs N_sc
    plt.figure(figsize=(10, 6))
    plt.plot(df["q"], df["N_sc"], marker="o", linestyle="-", color="g", label="N_sc")
    plt.xlabel("Probabilidad de Percolación (q)")
    plt.ylabel("N_sc")
    plt.title("N_sc vs Probabilidad de Percolación")
    plt.legend()
    plt.grid()
    plt.savefig(f'{output_photo_base}_n_sc.png')  # Save plot
    plt.show()

# Parameters for the program execution
executable = "./programa"  # Update with the path to your executable
dimacs_file = input("Enter a DIMACS file to read the graph: \n")
percolation_type = input("Do you want Bond(1) or Site(2) percolation: \n")  # 1 for Bond Percolation, 2 for Site Percolation
step = input("Enter the step: \n")
percolationThreshold = 0.0
output_photo_base = input("Enter the base name for the output graph files (without extension): \n")
excelFile = input("Enter the Excel file to save the results: \n")

for i in range(1, 3):
    print("Running execution: ", i)
    results, percolationThreshold = run_percolation_program(executable, dimacs_file, percolation_type, step)
    if results:
        save_results_to_excel(results, excelFile, percolationThreshold)
    

# Plot the results from the Excel file
plot_results(excelFile, output_photo_base)
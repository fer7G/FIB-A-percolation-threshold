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
            # Extract values of q and number of connected components
            parts = line.split(", ")
            q_value = float(parts[0].split("= ")[1])
            num_components = int(parts[1].split("= ")[1])
            results.append((q_value, num_components))

        elif line.startswith("Percolación detectada a q = "):
            percolationThreshold = float(line.split("= ")[1])
            print(percolationThreshold)

    return results,percolationThreshold

def save_results_to_excel(results, filename, percolThresh):
    df_cols = pd.DataFrame(results, columns=['q', 'Componentes Conexos'])
    df_espacio = pd.DataFrame(columns=['q', 'Componentes Conexos'], index=[-1])  # Using -1 or another unique index
    df_percolThresh = pd.DataFrame({'Umbral de Percolación': [percolThresh]})

    if os.path.exists(filename):
        df_existente = pd.read_excel(filename)
        df_total = pd.concat([df_existente, df_espacio, df_cols, df_percolThresh], ignore_index=True)
    else:
        df_total = df_cols

    # Guardar el archivo actualizado
    df_total.to_excel(filename, index=False)
    print("Resultados acumulados guardados en ",filename)

def plot_results(filename, outputPhoto):
    # Load the Excel file
    df = pd.read_excel(filename)
    
    # Plot q values vs. number of connected components
    plt.figure(figsize=(10, 6))
    plt.plot(df["q"], df["Componentes Conexos"], marker="o", linestyle="-", color="b", label="Connected Components")
    plt.xlabel("Probabilidad de Percolación (q)")
    plt.ylabel("Número de Componentes Conexos")
    plt.title("Componentes Conexos vs Probabilidad de Percolación")
    plt.legend()
    plt.grid()
    plt.savefig(outputPhoto)  # Save the plot as a file
    plt.show()


# Parameters for the program execution
executable = "./programa"  # Update this with the path to your executable
dimacs_file = input("Enter a dimacs file to read the graph: \n")
percolation_type = input("Do you want Bond(1) or Site(2) percolation: \n")  # 1 for Bond Percolation, 2 for Site Percolation
step = input("Enter the step: \n")
percolationThreshold = 0.0
outputPhoto = input("Enter a file to output the graph: \n")
excelFile = input("Enter the excel file: \n")

for i in range(1,10):
    print("Running execution: ", i)
    results,percolationThreshold = run_percolation_program(executable, dimacs_file, percolation_type, step)
    save_results_to_excel(results, excelFile, percolationThreshold)


plot_results(excelFile, outputPhoto)

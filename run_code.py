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

    return results

def save_results_to_excel(results, filename):
    df_cols = pd.DataFrame(results, columns=['q', 'Componentes Conexos'])
    df_espacio = pd.DataFrame(columns=['q', 'Componentes Conexos'], index=[-1])  # Using -1 or another unique index

    #Comprueba que el archivo exista, y en caso
    if os.path.exists("resultados_percolacion.xlsx"):
        df_existente = pd.read_excel("resultados_percolacion.xlsx")
        df_total = pd.concat([df_existente, df_espacio, df_cols], ignore_index=True)
    else:
        df_total = df_cols

    # Guardar el archivo actualizado
    df_total.to_excel("resultados_percolacion.xlsx", index=False)
    print("Resultados acumulados guardados en 'resultados_percolacion.xlsx'")

def plot_results(filename):
    # Load the Excel file
    df = pd.read_excel(filename, sheet_name="Percolation Results")
    
    # Plot q values vs. number of connected components
    plt.figure(figsize=(10, 6))
    plt.plot(df["q"], df["Connected Components"], marker="o", linestyle="-", color="b", label="Connected Components")
    plt.xlabel("Percolation Probability (q)")
    plt.ylabel("Number of Connected Components")
    plt.title("Connected Components vs Percolation Probability")
    plt.legend()
    plt.grid()
    plt.show()


# Parameters for the program execution
executable = "./programa"  # Update this with the path to your executable
dimacs_file = "erdos.dimacs"
percolation_type = 1  # 1 for Bond Percolation, 2 for Site Percolation
step = 0.1

# Run the C++ program and collect results
results = run_percolation_program(executable, dimacs_file, percolation_type, step)

# Save to Excel if results were obtained
if results:
    save_results_to_excel(results, "results_percolation.xlsx")
    plot_results("results_percolation.xlsx")

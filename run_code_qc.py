import subprocess
import pandas as pd
import matplotlib.pyplot as plt
import numpy as np

def run_percolation_program(executable, dimacs_file, percolation_type, step):
    # Run the C++ program and capture the output
    result = subprocess.run(
        [executable],
        input=f"{dimacs_file}\n{percolation_type}\n{step}\n",
        text=True,
        capture_output=True
    )
    if result.returncode != 0:
        print("Error running the program:", result.stderr)
        return None

    percolationThreshold = None
    for line in result.stdout.splitlines():
        if line.startswith("Percolación detectada a q = "):
            percolationThreshold = float(line.split("= ")[1])
            break

    return percolationThreshold

def cumulative_percolation_probability(thresholds, q_values):
    # Initialize an array to count percolation occurrences at each q value
    percolation_count = np.zeros(len(q_values))

    # For each threshold, mark all q-values greater than or equal to it
    for threshold in thresholds:
        for i, q in enumerate(q_values):
            if q >= threshold:
                percolation_count[i] += 1

    # Calculate cumulative probability as fraction of total iterations
    cumulative_probability = percolation_count / len(thresholds)
    return cumulative_probability

def plot_cumulative_probability(q_values, cumulative_probabilities):
    plt.figure(figsize=(10, 6))
    plt.plot(q_values, cumulative_probabilities, marker="o", linestyle="-", color="g", label="Cumulative Percolation Probability")
    plt.xlabel("Probabilidad de Percolación (q)")
    plt.ylabel("Probabilidad Acumulativa")
    plt.title("Probabilidad Acumulativa de Percolación vs q")
    plt.legend()
    plt.grid()
    plt.savefig("cumulative_percolation_probability.png")  # Save the plot as a file
    plt.show()

# Parameters for the program execution
executable = "./programa"  # Update this with the path to your executable
dimacs_file = "malla_cuadrada.dimacs"
percolation_type = 2  # 1 for Bond Percolation, 2 for Site Percolation
step = 0.01

# Define q values between 0 and 1 at intervals of 0.01
q_values = np.arange(0, 1.01, step)
thresholds = []

# Run the simulation for a set number of iterations
num_iterations = 10
for i in range(num_iterations):
    print(f"Running iteration {i+1}")
    threshold = run_percolation_program(executable, dimacs_file, percolation_type, step)
    if threshold is not None:
        thresholds.append(threshold)

# Compute cumulative percolation probability
cumulative_probabilities = cumulative_percolation_probability(thresholds, q_values)

# Plot the cumulative percolation probability
plot_cumulative_probability(q_values, cumulative_probabilities) 
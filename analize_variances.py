import subprocess
import pandas as pd
import matplotlib.pyplot as plt
import os
import numpy as np  # To calculate variance

def run_percolation_program(executable, dimacs_file, percolation_type, step):
    # Run the C++ program and capture the output
    result = subprocess.run(
        [executable],
        input=f"{dimacs_file}\n{percolation_type}\n{step}\n",
        text=True,
        capture_output=True
    )
    #print(result.stdout)

    # Check for errors
    if result.returncode != 0:
        print("Error running the program:", result.stderr)
        return None, None
    
    percolationThreshold = 0.0

    # Parse output to retrieve results
    results = []
    for line in result.stdout.splitlines():
        if line.startswith("q ="):
            # Extract values of q and number of connected components
            parts = line.split(", ")
            q_value = float(parts[0].split("= ")[1])
            num_components = int(parts[1].split("= ")[1])
            results.append((q_value, num_components))

        elif line.startswith("Percolación detectada a q ="):
            percolationThreshold = float(line.split("= ")[1])
            print(f"Percolation threshold detected: q = {percolationThreshold}\n")
    
    return results, percolationThreshold


def plot_variance_vs_iterations(iterations, variances):
    # Plot the variance vs number of iterations
    plt.figure(figsize=(10, 6))
    plt.plot(iterations, variances, marker="o", linestyle="-", color="r", label="Variance")
    plt.xlabel("Number of Iterations")
    plt.ylabel("Variance of Percolation Threshold")
    plt.title("Variance of Percolation Threshold vs Number of Iterations")
    plt.legend()
    plt.grid()
    plt.savefig("variance_percolation_iterations2.png")  # Save the plot as a file
    plt.show()


# Parameters for the program execution
executable = "./programa"  # Update this with the path to your executable
dimacs_file = "malla_cuadrada.dimacs"
percolation_type = 1  # 1 for Bond Percolation, 2 for Site Percolation
step = 0.01

# To store percolation thresholds from each iteration
thresholds = []
iterations = []
variances = []

# Perform growing iterations: first 100, then 200, ..., up to 1000 iterations
for i in range(10, 101, 10):
    print(f"Running {i} iterations")
    
    for j in range(i - len(thresholds)):  # Only run new iterations
        results, percolationThreshold = run_percolation_program(executable, dimacs_file, percolation_type, step)
        
        if percolationThreshold is not None:
            thresholds.append(percolationThreshold)


    # Calculate the variance for the current number of iterations
    if thresholds:
        variance = np.var(thresholds)
        iterations.append(i)
        variances.append(variance)
        print(f"Variance after {i} iterations: {variance}")

# Calculate total variance after 1000 iterations
total_variance = np.var(thresholds)
print(f"Total variance after 1000 iterations: {total_variance}")

# # Calculate explained variance percentage for each iteration set
# for i in range(30, 901, 30):
#     current_variance = np.var(thresholds[:i])
#     explained_variance_percentage = (current_variance / total_variance) * 100
#     explained_variances.append(explained_variance_percentage)
#     iterations.append(i)
#     print(f"Explained variance after {i} iterations: {explained_variance_percentage}%")

# Plot explained variance as a function of the number of iterations
plot_variance_vs_iterations(iterations, variances)
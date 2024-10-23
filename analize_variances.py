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
    
    p_c = 0.0

    # Parse output to retrieve results
    results = []
    for line in result.stdout.splitlines():
        if line.startswith("p ="):
            # Extract values of p and number of connected components
            parts = line.split(", ")
            p = float(parts[0].split("= ")[1])
            Ncc = int(parts[1])
            Smax = int(parts[2])
            Nmax = float(parts[3])
            results.append((p, Ncc, Smax, Nmax))

        elif line.startswith("Percolación detectada a p ="):
            p_c = float(line.split("= ")[1])
            print(f"Percolation threshold detected: p = {p_c}\n")
    
    return results, p_c


def plot_variance_vs_iterations(iterations, variances, variance_means):
    # Plot the variance vs number of iterations with smaller dots
    plt.figure(figsize=(10, 6))
    plt.plot(iterations, variances, marker="o", linestyle="-", color="r", label="Variance", markersize=2)  # Adjust markersize
    
    # Plot the cumulative mean of the variances
    plt.plot(iterations, variance_means, linestyle="--", color="b", label="Mean Variance")
    
    plt.xlabel("Number of Iterations")
    plt.ylabel("Variance of Percolation Threshold")
    plt.title("Variance and Mean of Percolation Threshold Variance vs Number of Iterations")
    plt.legend()
    plt.grid()
    plt.savefig("variance_percolation_iterations_with_mean.png")
    plt.show()


# Parameters
executable = "./programa"  # Path to the C++ executable
dimacs_file = "malla.dimacs"  # DIMACS file
percolation_type = 1  # Bond(1) or Site(2) percolation
step = 0.01  # Step for p
epsilon = 6e-8  # Threshold for variance stability
max_iterations = 10000  # Maximum number of iterations
window_size = 15  # Number of iterations to check for stability

# Initialize variables
thresholds = []
iterations = []
variances = []
variance_means = []

for i in range(1, max_iterations + 1):
    print(f"Running iteration {i}")
    
    # Run the C++ program and get results
    results, p_c = run_percolation_program(executable, dimacs_file, percolation_type, step)
    
    if p_c is not None:
        thresholds.append(p_c)

    # Calculate the variance for the current number of thresholds
    if len(thresholds) > 1:
        variance = np.var(thresholds)
        iterations.append(i)
        variances.append(variance)
        
        # Calculate cumulative mean of variance
        variance_mean = np.mean(variances)
        variance_means.append(variance_mean)
        
        print(f"Variance after {i} iterations: {variance}")
        print(f"Mean of variance after {i} iterations: {variance_mean}")

        # Check variance stabilization over the rolling window
        if len(variances) > window_size:
            # Calculate the average change in variance over the window
            variance_changes = [
                abs(variances[-(k+1)] - variances[-(k+2)]) for k in range(window_size-1)
            ]
            avg_change_in_variance = np.mean(variance_changes)

            print(f"Average change in variance over the last {window_size} iterations: {avg_change_in_variance}")

            if avg_change_in_variance < epsilon:
                print(f"Variance has stabilized at iteration {i}")
                break
    else:
        # If only one threshold, variance is zero
        variances.append(0)
        variance_means.append(0)
        iterations.append(i)

# Calculate total variance after the final iteration
total_variance = np.var(thresholds)
print(f"Total variance after {i} iterations: {total_variance}")

# Plot the variance vs iterations with the mean variance
plot_variance_vs_iterations(iterations, variances, variance_means)
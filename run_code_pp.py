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

def smooth_curve(y, box_pts):
    """Applies a moving average to smooth the curve"""
    box = np.ones(box_pts) / box_pts
    y_smooth = np.convolve(y, box, mode='same')
    return y_smooth

def plot_cumulative_probability(q_values, cumulative_probabilities_list, dimacs_files):
    plt.figure(figsize=(10, 6))

    # Plot P_max vs p for each file with smoothing applied
    for cumulative_probabilities, dimacs_file in zip(cumulative_probabilities_list, dimacs_files):
        # Apply a moving average smoothing to the cumulative probabilities
        smooth_cumulative_probabilities = smooth_curve(cumulative_probabilities, box_pts=5)

        # Plot the smoothed curve
        plt.plot(q_values, smooth_cumulative_probabilities, marker="o", linestyle="-", label=f"{dimacs_file}", markersize=2)

    plt.xlabel("p")
    plt.ylabel("P_max")
    plt.title("P_max vs p for Multiple DIMACS Files (Smoothed with Moving Average)")
    plt.legend()
    plt.grid()
    plt.savefig("p_p_multi.png")  # Save the plot as a file
    plt.show()

# Parameters for the program execution
executable = "./programa"  # Update this with the path to your executable
dimacs_files = ["20malla","100malla","200malla", "500malla","800malla", "1000malla"]  # Add your DIMACS files here
percolation_type = 2  # 1 for Bond Percolation, 2 for Site Percolation
step = 0.01

# Define q values between 0 and 1 at intervals of 0.01
q_values = np.arange(0, 1.01, step)

# List to store cumulative probabilities for each DIMACS file
cumulative_probabilities_list = []

# Run the simulation for each DIMACS file
num_iterations = 100
for dimacs_file in dimacs_files:
    thresholds = []  # Reset thresholds for each file

    for i in range(num_iterations):
        print(f"Running iteration {i+1} for {dimacs_file}")
        threshold = run_percolation_program(executable, dimacs_file, percolation_type, step)
        if threshold is not None:
            thresholds.append(threshold)

    # Compute cumulative percolation probability for the current file
    cumulative_probabilities = cumulative_percolation_probability(thresholds, q_values)
    cumulative_probabilities_list.append(cumulative_probabilities)

# Plot the cumulative percolation probability for all DIMACS files
plot_cumulative_probability(q_values, cumulative_probabilities_list, dimacs_files)
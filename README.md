# Percolation threshold

<p align="center">
  <img src="./percolation.gif" width="400" alt="Percolation process animation"/>
  <br>
  <em>Figure: Percolation process visualized on a 500×500 lattice</em>
</p>

This project was developed as part of the Algorithmics course (Q1 2024–2025) at [FIB‑UPC](https://www.fib.upc.edu/) by [David Castro](https://github.com/davidc91x), [Fernando Guirao](https://github.com/fer7G), [Álvaro Monclús](https://github.com/amonclus) and [Aleix Ortigosa](https://github.com/aleix-oc).

## Abstract

**Percolation theory** is a research area within statistical physics and mathematics that studies the behavior of complex systems and networks under random connectivity processes. This project explores the classic percolation problem on graphs representing squared lattices, random geometric graphs (RGGs), and Kagome graphs. The main focus is the **percolation threshold**, the critical point at which a geometric **phase transition** occurs, typically characterized by the emergence of a large connected cluster in the network.

The [project report](./docs/report.pdf) (only in Spanish at the moment) includes a brief introduction to percolation and an implemented model based on existing literature. A series of experiments are conducted to estimate the percolation threshold and study the phenomena surrounding it.

## Test it yourself!

### Requirements

#### C++ dependencies

- A C++17-compliant compiler (e.g. `g++ >= 7`)
- `make` utility

Just run `make` in the root directory to compile the program.

#### Python dependencies (for visualization)

You can install the required Python packages using:

```bash
$ pip install -r requirements.txt
```


### Simulate percolation process

From the project’s root directory, compile the C++ program that simulates the percolation process using the Makefile:

```zsh
$ make
```

Then go to the `build/` folder and run the program:

```zsh
$ ./program
```

Follow the prompts to set your preferences for the simulation. Here's an example:

```
Enter the DIMACS file name: lattice.dimacs
Choose percolation type:
1. Bond percolation
2. Site percolation
Option: 1
Enter the step value for p (between 0 and 1): 0.1
Do you want to save the position of each node at each step for later visualization? (0 = No, 1 = Yes): 1
Percolation detected at p = 0.6
Execution time: 0.28587 seconds
Complete bond percolation results:
p		Connected Components	Smax		Nmax
0		250000			        1		    4e-06
0.1		200381			        12		    4.8e-05
0.2		150884			        26		    0.000104
0.3		102840			        65		    0.00026
0.4		59035			        324		    0.001296
0.5		25183			        71528		0.286112
0.6		8599			        236829		0.947316
0.7		2481			        246969		0.987876
0.8		472			            249486		0.997944
0.9		26			            249975		0.9999
1		1			            250000		1
```

We provide a squared lattice of $500 \times 500$ nodes on `data/lattice.dimacs` for testing.

If enabled, the cluster assignment of each node for every value of $p$ will be saved to `data/cluster_of_each_node.csv`. This file can then be used to visualize the percolation process (explained in the next section). While other approaches might be more elegant, we chose this method to keep the core C++ logic simple and efficient.

### Visualize percolation process

First, make sure you’ve set up a Python virtual environment and installed the required packages. Then go to the `/scripts` folder and locate the `visualize_percolation.py` script.

In the script’s main section, specify the number of nodes in the grid (default is $500$ if you use `lattice.dimacs`) and the delay between each step of $p$ (default is 1 second). For lattices larger than $500 \times 500$, the execution time may increase significantly — that size is already sufficient for meaningful visualizations. Depending on the chosen step size, you can reduce the delay to make the animation smoother.

```zsh
$ python3 visualize_percolation.py
```

### Rest of scripts

The rest of the scripts in the `/scripts` folder were used to run the experiments included in the report. However, they are currently outdated and may not work.

## References

The visualization implementation was inspired by [Spectral Collective’s YouTube video](https://youtu.be/a-767WnbaCQ?si=gPt8hE1LRL2VYPW2).

All academic references used throughout the project can be found in the bibliography section of the [project report](./docs/report.pdf).
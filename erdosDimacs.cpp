using namespace std;

#include <iostream>
#include <vector>
#include <fstream>
#include <cstdlib>
#include <ctime>

// Function to generate an Erdős–Rényi random graph as an adjacency matrix
vector< vector <int> > generate_erdos_renyi_graph(int n, double p) {
    vector< vector <int> > adjacency_matrix(n, vector<int>(n, 0));
    srand(time(0)); // Seed the random number generator

    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) { // Only upper triangle to avoid self-loops and double connections
            double random_val = static_cast<double>(rand()) / RAND_MAX;
            if (random_val < p) {
                adjacency_matrix[i][j] = 1;
                adjacency_matrix[j][i] = 1; // Symmetric for undirected graph
            }
        }
    }
    return adjacency_matrix;
}

// Function to write the graph in DIMACS format to a file
void write_graph_to_dimacs(const vector< vector<int> >& adjacency_matrix, const string& filename) {
    int n = adjacency_matrix.size();
    int edge_count = 0;

    // Calculate the total number of edges
    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            if (adjacency_matrix[i][j] == 1) {
                ++edge_count;
            }
        }
    }

    // Open the file
    ofstream file(filename);
    if (!file.is_open()) {
        cerr << "Error opening file!\n";
        return;
    }

    // Write DIMACS header
    file << "p edge " << n << " " << edge_count << "\n";

    // Write each edge in the form "e <node1> <node2>"
    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            if (adjacency_matrix[i][j] == 1) {
                file << "e " << (i + 1) << " " << (j + 1) << "\n"; // DIMACS format is 1-indexed
            }
        }
    }

    file.close();
    cout << "Graph written to " << filename << " in DIMACS format.\n";
}

int main() {
    int n;
    double p;
    
    cout << "Enter the number of nodes (n): ";
    cin >> n;
    cout << "Enter the probability of edge creation (p): ";
    cin >> p;

    // Generate the graph
    vector< vector<int> > graph = generate_erdos_renyi_graph(n, p);

    // Write the graph to file in DIMACS format
    write_graph_to_dimacs(graph, "erdos.dimacs");

    return 0;
}
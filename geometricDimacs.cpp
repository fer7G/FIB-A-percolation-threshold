#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <cstdlib>
#include <ctime>

using namespace std;

// Structure to represent a node with x, y coordinates
struct Node {
    double x, y;
};

// Function to calculate the Euclidean distance between two nodes
double distance(const Node& a, const Node& b) {
    return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}

// Function to generate a random geometric graph
void generate_random_geometric_graph(int num_nodes, double radius, const string& filename) {
    vector<Node> nodes(num_nodes);
    vector< pair<int, int> > edges;

    // Initialize random seed
    srand(time(0));

    // Generate random positions for nodes in the unit square [0, 1] x [0, 1]
    for (int i = 0; i < num_nodes; ++i) {
        nodes[i].x = static_cast<double>(rand()) / RAND_MAX;
        nodes[i].y = static_cast<double>(rand()) / RAND_MAX;
    }

    // Check all pairs of nodes and add an edge if they are within the radius
    for (int i = 0; i < num_nodes; ++i) {
        for (int j = i + 1; j < num_nodes; ++j) {
            if (distance(nodes[i], nodes[j]) <= radius) {
                edges.emplace_back(i + 1, j + 1);  // Add edge (i, j)
            }
        }
    }

    // Write the graph to a file in DIMACS format
    ofstream outfile(filename);
    if (!outfile.is_open()) {
        cerr << "Error: Could not open the file " << filename << endl;
        return;
    }

    // Write the header in DIMACS format
    outfile << "c Random Geometric Graph" << endl;
    outfile << "p edge " << num_nodes << " " << edges.size() << endl;

    // Write the edges
    for (const auto& edge : edges) {
        outfile << "e " << edge.first << " " << edge.second << endl;
    }

    outfile.close();
    cout << "Graph written to " << filename << " in DIMACS format." << endl;
}

int main() {
    int num_nodes;
    double radius;
    string filename;

    // Get user input
    cout << "Enter the number of nodes: ";
    cin >> num_nodes;
    cout << "Enter the radius: ";
    cin >> radius;
    cout << "Enter the output filename: ";
    cin >> filename;

    // Generate the random geometric graph and save it to a file
    generate_random_geometric_graph(num_nodes, radius, filename);

    return 0;
}
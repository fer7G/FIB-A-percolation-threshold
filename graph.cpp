using namespace std;
#include <iostream>
#include <vector>
#include <sstream>
#include <fstream>

class Graph
{
private:
    int numNodes;
    vector< vector<int> > adjList;

public:
    explicit Graph()
    {
        numNodes = 0;
        adjList.resize(0);
    }

    void addEdge(int u, int v)
    {
        adjList[u].push_back(v);
        adjList[v].push_back(u);
    }

    void printGraph() const
    {
        for(int i = 0; i < numNodes; i++)
        {
            for(int j : adjList[i])
            {
                cout << j << " ";
            }
            cout << endl;
        }
    }

    void readFile()
    {
        string line;
        char c;
        int u, v, n, m;

        while (getline(cin, line))
        {
            istringstream iss(line);
            if (!(iss >> c)) continue; // Skip empty lines

            if (c == 'c')
            {
                continue;
            }
            if (c == 'p')
            {
                string type;
                iss >> type >> n >> m;
                numNodes = n;
                adjList.resize(n);
            }
            else if (c == 'e')
            {
                iss >> u >> v;
                addEdge(u - 1, v - 1);
            }
        }
    }
};

int main()
{
    Graph g;

    // Open the DIMACS file
    ifstream inputFile("test.dimacs");

    if (!inputFile.is_open()) {
        cerr << "Error: Could not open file test.dimacs" << endl;
        return 1;
    }

    // Redirect the file input to cin temporarily
    cin.rdbuf(inputFile.rdbuf());  // Redirect cin to read from the file

    // Read the graph data from the file
    g.readFile();

    // Close the file after reading
    inputFile.close();

    // Print the graph to standard output
    g.printGraph();
}

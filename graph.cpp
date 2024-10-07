using namespace std;
#include <iostream>
#include <vector>
#include <sstream>
#include <fstream>
#include <random>


#define FILE_NAME "test.dimacs"
#define Matrix vector < vector <int> >

struct Graph
{
    int numNodes;
    Matrix adjList;

    Graph() {
        numNodes = 0;
        adjList.resize(0);
    }

    void add_edge(int u, int v){
        adjList[u].push_back(v);
        adjList[v].push_back(u);
    }

    void print_graph() const{
        for(int i = 0; i < numNodes; i++){
            for(int j : adjList[i]){
                cout << j << " ";
            }
            cout << endl;

        }
    }

    int countEdges() {
        int edgeCount = 0;
        for (const auto& neighbors : adjList) {
            edgeCount += neighbors.size();
        }
        return edgeCount / 2; 
    }

    void read_file(){
        string line;
        char c;
        int u, v, n, m;

        while (getline(cin, line)){
            istringstream iss(line);
            if (!(iss >> c)) continue; // Skip empty lines

            if (c == 'c'){
                continue;
            }
            if (c == 'p'){
                string type;
                iss >> type >> n >> m;
                numNodes = n;
                adjList.resize(n);
            }
            else if (c == 'e'){
                iss >> u >> v;
                add_edge(u - 1, v - 1);
            }
        }
    }

    void dfs(int node, vector<bool>& visited) {
        visited[node] = true;
        for (int neighbor : adjList[node]) {
            if (!visited[neighbor]) {
                dfs(neighbor, visited);
            }
        }
    }

    int connected_components() {
        vector<bool> visited(numNodes, false);
        int numComponents = 0;

        for (int i = 0; i < numNodes; ++i) {
            if (!visited[i]) {
                numComponents++;
                dfs(i, visited);  
            }
        }

        return numComponents;
    }

};


int main()
{
    
    // Graph g;
    // // Open the DIMACS file
    // ifstream inputFile(FILE_NAME);

    // if (!inputFile.is_open()) {
    //     cerr << "Error: Could not open file" << endl;
    //     return 1;
    // }

    // cin.rdbuf(inputFile.rdbuf());  // Redirect cin to read from the file
    // g.read_file();
    // inputFile.close();

    // cout << "The graph has " << g.connected_components() << " connected components" << endl;
    int result = system("python3 graph_generator.py");
        if (result == 0) {
        std::cout << "Python script executed successfully!" << std::endl;
    } else {
        std::cerr << "Failed to execute the Python script." << std::endl;
    }
    cout << "pito" << endl;
}


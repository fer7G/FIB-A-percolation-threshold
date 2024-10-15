#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <utility>
#include <fstream>
#include <sstream>
#include <unordered_set>

using namespace std;

typedef pair<int, int> Edge;

// Clase para Union-Find (Disjoint Set)
class UnionFind {
public:
    vector<int> parent, size;

    UnionFind(int n) {
        parent.resize(n);
        size.resize(n, 1);
        for (int i = 0; i < n; ++i) parent[i] = i;
    }

    int find(int u) {
        if (parent[u] != u)
            parent[u] = find(parent[u]);
        return parent[u];
    }

    void unite(int u, int v) {
        int rootU = find(u);
        int rootV = find(v);
        if (rootU != rootV) {
            if (size[rootU] < size[rootV]) swap(rootU, rootV);
            parent[rootV] = rootU;
            size[rootU] += size[rootV];
        }
    }

    int numComponents(int n) {
        unordered_set<int> unique_roots;
        for (int i = 0; i < n; ++i) {
            unique_roots.insert(find(i));
        }
        return unique_roots.size();
    }
};

// Función para realizar percolación por nodos
void percolacionPorNodos(int n, vector<Edge>& aristas, double q) {
    UnionFind uf(n);
    vector<bool> nodoActivo(n, true);
    srand(time(0));

    for (int i = 0; i < n; ++i) {
        if (static_cast<double>(rand()) / RAND_MAX >= q) {
            nodoActivo[i] = false;
        }
    }

    for (const auto& arista : aristas) {
        int u = arista.first, v = arista.second;
        if (nodoActivo[u] && nodoActivo[v]) {
            uf.unite(u, v);
        }
    }

    int componentesConexas = uf.numComponents(n);
    cout << "Componentes conexas después de la percolación por nodos: " << componentesConexas << endl;
}

// Función para cargar un grafo desde un archivo DIMACS
vector<Edge> cargarGrafoDIMACS(const string& nombreArchivo, int &numNodos) {
    ifstream archivo(nombreArchivo);
    vector<Edge> aristas;
    string linea;

    if (!archivo.is_open()) {
        cerr << "No se pudo abrir el archivo." << endl;
        return aristas;
    }

    while (getline(archivo, linea)) {
        if (linea[0] == 'c') continue;
        if (linea[0] == 'p') {
            stringstream ss(linea);
            string aux;
            ss >> aux >> aux >> numNodos;
        }
        else if (linea[0] == 'e') {
            stringstream ss(linea);
            char tipo;
            int u, v;
            ss >> tipo >> u >> v;
            aristas.push_back({u - 1, v - 1});  // Ajustar índices para 0-based
        }
    }

    archivo.close();
    return aristas;
}

// Función principal
int main() {
    string nombreArchivo;
    double q;
    cout << "Introduce el nombre del archivo DIMACS: ";
    cin >> nombreArchivo;
    cout << "Introduce el valor de q: ";
    cin >> q;
    
    int numNodos;
    vector<Edge> aristas = cargarGrafoDIMACS(nombreArchivo, numNodos);

    if (aristas.empty()) {
        cerr << "El grafo no se pudo cargar." << endl;
        return 1;
    }

    percolacionPorNodos(numNodos, aristas, q);

    return 0;
}
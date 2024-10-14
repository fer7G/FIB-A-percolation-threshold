#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <utility>
#include <fstream>    // Para ifstream y ofstream
#include <sstream>    // Para stringstream

using namespace std;

typedef pair<int, int> Edge;  // Tipo para representar una arista entre dos nodos

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
        int count = 0;
        for (int i = 0; i < n; ++i) {
            if (parent[i] == i) ++count;
        }
        return count;
    }
};

// Función para generar una configuración de pesos aleatorios para las aristas
vector<pair<Edge, double>> generarConfiguracion(const vector<Edge>& aristas) {
    vector<pair<Edge, double>> configuracion;
    srand(time(0));

    for (const auto& arista : aristas) {
        double peso = static_cast<double>(rand()) / RAND_MAX;  // Peso aleatorio entre 0 y 1
        configuracion.push_back({arista, peso});
    }

    return configuracion;
}

// Función para percolar el grafo
int percolarGrafo(int numNodos, const vector<pair<Edge, double>>& configuracion, double q) {
    UnionFind uf(numNodos);

    for (const auto& [arista, peso] : configuracion) {
        if (peso <= q) {  // Si el peso es mayor o igual a q, la arista se mantiene
            uf.unite(arista.first, arista.second);
        }
    }

    return uf.numComponents(numNodos);  // Devuelve el número de componentes conexos
}

// Función para leer un archivo DIMACS y extraer las aristas
vector<Edge> leerDimacs(const string& nombreArchivo, int& numNodos) {
    ifstream archivo(nombreArchivo);
    vector<Edge> aristas;
    string linea;

    if (!archivo.is_open()) {
        cerr << "Error al abrir el archivo!" << endl;
        return aristas;
    }

    while (getline(archivo, linea)) {
        if (linea[0] == 'c') {
            // Ignorar líneas de comentario
            continue;
        } else if (linea[0] == 'p') {
            // Leer la línea del problema
            stringstream ss(linea);
            string aux;
            int numAristas;
            ss >> aux >> aux >> numNodos >> numAristas;  // "p edge N M"
        } else if (linea[0] == 'e') {
            // Leer las aristas
            stringstream ss(linea);
            char aux;
            int u, v;
            ss >> aux >> u >> v;
            aristas.push_back({u - 1, v - 1});  // Convertir a 0-indexado
        }
    }

    archivo.close();
    return aristas;
}

int main() {
    string nombreArchivo;
    cin >> nombreArchivo;

    int numNodos;
    vector<Edge> aristas = leerDimacs(nombreArchivo, numNodos);

    if (aristas.empty()) {
        cerr << "Error: No se pudieron leer las aristas del archivo!" << endl;
        return -1;
    }

    // Generar la configuración de pesos aleatorios para las aristas
    vector<pair<Edge, double>> configuracion = generarConfiguracion(aristas);

    // Pedir valor de q
    double q;
    cin >> q;

    // Percolar el grafo y obtener el número de componentes conexos
    int numComponentesConexos = percolarGrafo(numNodos, configuracion, q);

    cout << "Número de componentes conexos después de percolar con q = " << q << ": " << numComponentesConexos << endl;

    return 0;
}

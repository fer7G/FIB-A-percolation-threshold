#include "SitePercolation.h"
#include <cstdlib>
#include <ctime>

/**
 * Constructor que inicializa la clase con el número de nodos.
 */
SitePercolation::SitePercolation(int numNodos) : uf(numNodos), numNodos(numNodos) {}

/**
 * Genera una configuración de pesos aleatorios para los vértices.
 */
vector<double> SitePercolation::generate_configuration() {
    vector<double> configuracion(numNodos);
    srand(time(0));

    for (int i = 0; i < numNodos; ++i) {
        configuracion[i] = static_cast<double>(rand()) / RAND_MAX;  // Peso aleatorio entre 0 y 1
    }

    return configuracion;
}

/**
 * Realiza una percolación para un valor dado de q y devuelve el número de componentes conexos.
 */
int SitePercolation::generate_single_percolation(const vector<Edge>& aristas, const vector<double>& configuracion, double q) {
    uf = UnionFind(numNodos);  // Reiniciar el estado de UnionFind para cada percolación
    vector<bool> nodoActivo(numNodos, false);  // Vector que indica si un nodo está activo

    // Marcar nodos activos según el valor de q
    for (int i = 0; i < numNodos; ++i) {
        if (configuracion[i] >= q) {
            nodoActivo[i] = true;  // El nodo se mantiene activo
        }
    }

    // Conectar solo los nodos activos
    for (const auto& arista : aristas) {
        int u = arista.first;
        int v = arista.second;
        if (nodoActivo[u] && nodoActivo[v]) {  // Unir solo nodos activos
            uf.unite(u, v);
        }
    }

    return uf.numComponents(numNodos);  // Devuelve el número de componentes conexos
}

/**
 * Realiza una percolación completa para valores de q entre 0 y 1, y devuelve la relación
 * entre q y el número de componentes conexos.
 */
vector<pair<double, int>> SitePercolation::generate_full_percolation(const vector<Edge>& aristas, const vector<double>& configuracion, double step) {
    vector<pair<double, int>> resultados;

    // Recorremos los valores de q entre 0 y 1 usando el step
    for (double q = 0.0; q <= 1.0; q += step) {
        int numComponentes = generate_single_percolation(aristas, configuracion, q);
        resultados.push_back({q, numComponentes});
    }

    return resultados;
}

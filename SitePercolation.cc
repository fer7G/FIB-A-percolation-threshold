#include "SitePercolation.h"
#include <cstdlib>
#include <ctime>
#include <iostream>

/**
 * Constructor que inicializa la clase con el número de nodos.
 * Inicializa current_q en 0 para comenzar desde la percolación mínima.
 */
SitePercolation::SitePercolation(int numNodos) : uf(numNodos), numNodos(numNodos), current_q(0.0), nodoActivo(numNodos, false) {}

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
 * Realiza una percolación incremental. Solo se procesan los vértices cuyo peso esté entre current_q y el nuevo q.
 * El vector de nodos activos se va actualizando.
 */
int SitePercolation::generate_single_percolation(const vector<Edge>& aristas, const vector<double>& configuracion, double q) {
    if (q < current_q) {
        cerr << "Error: No se puede realizar una percolación con un q menor que el actual." << endl;
        return uf.numComponents(numNodos);  // Devuelve el número actual de componentes si no es válido
    }

    // Activar nodos cuya configuración esté entre current_q y el nuevo q
    for (int i = 0; i < numNodos; ++i) {
        if (!nodoActivo[i] && configuracion[i] <= q) {
            nodoActivo[i] = true;  // Activar el nodo si no lo estaba ya
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

    // Actualizar el valor actual de q
    current_q = q;

    return uf.numComponents(numNodos);  // Devuelve el número de componentes conexos actual
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

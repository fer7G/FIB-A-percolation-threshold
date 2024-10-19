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

    vector<int> top_nodes;    // Indices de los nodos de la fila superior
    vector<int> bottom_nodes; // Indices de los nodos de la fila inferior

    bool percolation = false;  // Bandera para indicar si se ha producido la percolación

    // Inicializar los nodos del top y bottom (esto depende del tamaño y estructura de la cuadrícula)
    int grid_size = sqrt(numNodos);  // Asumimos una cuadrícula cuadrada
    for (int i = 0; i < grid_size; ++i) {
        top_nodes.push_back(i);  // Los primeros nodos son del top
        bottom_nodes.push_back(numNodos - grid_size + i);  // Los últimos nodos son del bottom
    }

    // Recorremos los valores de q entre 0 y 1 usando el step
    for (double q = 0.0; q <= 1.0 + 1e-10; q += step) {
        int numComponentes = generate_single_percolation(aristas, configuracion, q);
        resultados.push_back({q, numComponentes});

        // Verificar si ya se ha producido la percolación
        if (not percolation) {
            percolation = has_percolation(top_nodes, bottom_nodes);
            if (percolation) cout << "Percolación detectada a q = " << q_c << endl;
        }
    }

    return resultados;
}

/**
 * Verifica si se ha producido la percolación, es decir, si existe un camino entre el top y el bottom.
 */
bool SitePercolation::has_percolation(const vector<int>& top_nodes, const vector<int>& bottom_nodes) {
    // Verificamos si algún nodo de la fila superior está conectado con algún nodo de la fila inferior
    for (int top_node : top_nodes) {
        for (int bottom_node : bottom_nodes) {
            if (uf.find(top_node) == uf.find(bottom_node)) {
                // Si están conectados, se ha producido la percolación
                q_c = current_q;  // Guardar el valor de q crítico
                return true;
            }
        }
    }
    return false;  // No se ha producido la percolación
}
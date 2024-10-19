#include "BondPercolation.h"
#include <cstdlib>
#include <ctime>
#include <iostream>

/**
 * Constructor que inicializa la clase con el número de nodos.
 * Inicializa current_q en 0 para comenzar desde la percolación mínima.
 */
BondPercolation::BondPercolation(int numNodos) : uf(numNodos), numNodos(numNodos), current_q(0.0) {}

/**
 * Genera una configuración de pesos aleatorios para las aristas.
 */
vector<pair<Edge, double>> BondPercolation::generate_configuration(const vector<Edge>& aristas) {
    vector<pair<Edge, double>> configuracion;
    srand(time(0));

    for (const auto& arista : aristas) {
        double peso = static_cast<double>(rand()) / RAND_MAX;  // Peso aleatorio entre 0 y 1
        configuracion.push_back({arista, peso});
    }

    return configuracion;
}

/**
 * Realiza una percolación incremental. Solo se procesan las aristas cuyo peso esté entre current_q y el nuevo q.
 */
int BondPercolation::generate_single_percolation(const vector<pair<Edge, double>>& configuracion, double q) {
    if (q < current_q) {
        cerr << "Error: No se puede realizar una percolación con un q menor que el actual." << endl;
        return uf.numComponents(numNodos);  // Devuelve el número actual de componentes si no es válido
    }

    // Solo procesar las aristas cuyo peso esté entre current_q y q
    for (const auto& [arista, peso] : configuracion) {
        if (peso > current_q && peso <= q) {
            uf.unite(arista.first, arista.second);  // Unir si el peso está en el rango correcto
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
vector<pair<double, int>> BondPercolation::generate_full_percolation(const vector<pair<Edge, double>>& configuracion, double step) {
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
        int numComponentes = generate_single_percolation(configuracion, q);
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
bool BondPercolation::has_percolation(const vector<int>& top_nodes, const vector<int>& bottom_nodes) {
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

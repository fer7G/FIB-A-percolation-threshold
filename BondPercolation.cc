#include "BondPercolation.h"
#include <cstdlib>
#include <ctime>

/**
 * Constructor que inicializa la clase con el número de nodos.
 */
BondPercolation::BondPercolation(int numNodos) : uf(numNodos), numNodos(numNodos) {}

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
 * Realiza una percolación para un valor dado de q y devuelve el número de componentes conexos.
 */
int BondPercolation::generate_single_percolation(const vector<pair<Edge, double>>& configuracion, double q) {
    uf = UnionFind(numNodos);  // Reiniciar el estado de UnionFind para cada percolación

    for (const auto& [arista, peso] : configuracion) {
        if (peso <= q) {  // Si el peso es menor o igual a q, la arista se mantiene
            uf.unite(arista.first, arista.second);
        }
    }

    return uf.numComponents(numNodos);  // Devuelve el número de componentes conexos
}

/**
 * Realiza una percolación completa para valores de q entre 0 y 1, y devuelve la relación
 * entre q y el número de componentes conexos.
 */
vector<pair<double, int>> BondPercolation::generate_full_percolation(const vector<pair<Edge, double>>& configuracion, double step) {
    vector<pair<double, int>> resultados;

    // Recorremos los valores de q entre 0 y 1 usando el step
    for (double q = 0.0; q <= 1.0; q += step) {
        int numComponentes = generate_single_percolation(configuracion, q);
        resultados.push_back({q, numComponentes});
    }

    return resultados;
}

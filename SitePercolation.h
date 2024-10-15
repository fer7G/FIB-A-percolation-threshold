#ifndef SITE_PERCOLATION_H
#define SITE_PERCOLATION_H

#include "UnionFind.h"
#include <vector>
#include <utility>
using namespace std;

typedef pair<int, int> Edge;  // Tipo para representar una arista entre dos nodos

class SitePercolation {
public:
    /**
     * Constructor que inicializa la clase con el número de nodos.
     *
     * @param numNodos Número total de nodos en el grafo.
     */
    SitePercolation(int numNodos);

    /**
     * Genera una configuración de pesos aleatorios para los vértices.
     *
     * @return Un vector de pesos aleatorios asociados a cada vértice.
     */
    vector<double> generate_configuration();

    /**
     * Realiza una percolación para un valor dado de q y devuelve el número de componentes conexos.
     *
     * @param aristas Vector de aristas del grafo.
     * @param configuracion Vector de pesos asociados a los vértices.
     * @param q Probabilidad de que un vértice no falle.
     * @return Número de componentes conexos después de la percolación.
     */
    int generate_single_percolation(const vector<Edge>& aristas, const vector<double>& configuracion, double q);

    /**
     * Realiza una percolación completa para valores de q entre 0 y 1, y devuelve la relación
     * entre q y el número de componentes conexos.
     *
     * @param aristas Vector de aristas del grafo.
     * @param configuracion Vector de pesos asociados a los vértices.
     * @param step Valor de paso para q.
     * @return Un vector de pares donde cada par es un valor de q y el número de componentes conexos.
     */
    vector<pair<double, int>> generate_full_percolation(const vector<Edge>& aristas, const vector<double>& configuracion, double step);

private:
    UnionFind uf;  // Objeto UnionFind para manejar la conectividad dinámica del grafo.
    int numNodos;  // Número de nodos en el grafo.
    double current_q; // Valor actual de q
    vector<bool> nodoActivo;  // Vector que indica si un nodo está activo
};

#endif

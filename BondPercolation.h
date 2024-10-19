#ifndef BOND_PERCOLATION_H
#define BOND_PERCOLATION_H

#include "UnionFind.h"
#include <vector>
#include <utility>
using namespace std;

typedef pair<int, int> Edge;  // Tipo para representar una arista entre dos nodos

class BondPercolation {
public:
    /**
     * Constructor que inicializa la clase con el número de nodos.
     *
     * @param numNodos Número total de nodos en el grafo.
     */
    BondPercolation(int numNodos);

    /**
     * Inicializa los supernodos conectando los nodos del top y bottom en la estructura auxiliar.
     */
    void initialize_supernodes();

    /**
     * Genera una configuración de pesos aleatorios para las aristas.
     *
     * @param aristas Vector de aristas del grafo.
     * @return Un vector de pares donde cada par es una arista y su peso aleatorio asociado.
     */
    vector<pair<Edge, double>> generate_configuration(const vector<Edge>& aristas);

    /**
     * Realiza una percolación para un valor dado de q y devuelve el número de componentes conexos.
     *
     * @param configuracion Vector con las aristas y sus pesos.
     * @param q Probabilidad de que una arista no falle.
     * @return Número de componentes conexos después de la percolación.
     */
    int generate_single_percolation(const vector<pair<Edge, double>>& configuracion, double q);

    /**
     * Realiza una percolación completa para valores de q entre 0 y 1, y devuelve la relación
     * entre q y el número de componentes conexos.
     *
     * @param configuracion Vector con las aristas y sus pesos.
     * @param step Valor de paso para q.
     * @return Un vector de pares donde cada par es un valor de q y el número de componentes conexos.
     */
    vector<pair<double, int>> generate_full_percolation(const vector<pair<Edge, double>>& configuracion, double step);

    /**
     * Función que verifica si se ha producido la percolación (si existe un camino del top al bottom).
     *
     * @return Verdadero si se ha producido la percolación, falso en caso contrario.
     */
    bool has_percolation();

    /**
     * Devuelve el valor de q crítico.
     *
     * @return q crítico, si se ha producido la percolación.
     */
    double get_critical_q() const { return q_c; }

private:
    UnionFind uf;  // Objeto UnionFind para manejar la conectividad dinámica del grafo.
    UnionFind uf_aux; // Estructura auxiliar para manejar los supernodos
    int numNodos;  // Número de nodos en el grafo.
    double current_q; // Valor actual de q
    double q_c;
    int superTop;
    int superBottom;
};

#endif

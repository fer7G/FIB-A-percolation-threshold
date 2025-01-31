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
     * Realiza una percolación para un valor dado de p y devuelve el número de componentes conexos.
     *
     * @param configuracion Vector con las aristas y sus pesos.
     * @param p Probabilidad de que una arista no falle.
     * @return Número de componentes conexos después de la percolación.
     */
    int generate_single_percolation(const vector<pair<Edge, double>>& configuracion, double p, int &Smax);

    /**
     * Realiza una percolación completa para valores de p entre 0 y 1, y devuelve la relación
     * entre p y el número de componentes conexos.
     *
     * @param configuracion Vector con las aristas y sus pesos.
     * @param step Valor de paso para p.
     * @return Un vector de pares donde cada par es un valor de p y el número de componentes conexos.
     */
    vector<tuple<double, int, int, double>> generate_full_percolation(const vector<pair<Edge, double>>& configuracion, double step, bool visualization);

    /**
     * Función que verifica si se ha producido la percolación (si existe un camino del top al bottom).
     *
     * @return Verdadero si se ha producido la percolación, falso en caso contrario.
     */
    bool has_percolation();

    /**
     * Devuelve el valor de p crítico.
     *
     * @return p crítico, si se ha producido la percolación.
     */
    double get_critical_p() const { return p_c; }

private:
    UnionFind uf;  // Objeto UnionFind para manejar la conectividad dinámica del grafo.
    UnionFind uf_aux; // Estructura auxiliar para manejar los supernodos
    int numNodos;  // Número de nodos en el grafo.
    double current_p; // Valor actual de p
    double p_c;
    int superTop;
    int superBottom;
};

#endif

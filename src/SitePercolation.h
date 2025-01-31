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
     * Inicializa los supernodos conectando los nodos del top y bottom en la estructura auxiliar.
     */
    void initialize_supernodes();

    /**
     * Genera una configuración de pesos aleatorios para los vértices.
     *
     * @return Un vector de pesos aleatorios asociados a cada vértice.
     */
    vector<double> generate_configuration();

    /**
     * Realiza una percolación para un valor dado de p y devuelve el número de componentes conexos.
     *
     * @param aristas Vector de aristas del grafo.
     * @param configuracion Vector de pesos asociados a los vértices.
     * @param p Probabilidad de que un vértice no falle.
     * @return Número de componentes conexos después de la percolación.
     */
    int generate_single_percolation(const vector<Edge>& aristas, const vector<double>& configuracion, double p, int &Smax);

    /**
     * Realiza una percolación completa para valores de p entre 0 y 1, y devuelve la relación
     * entre p y el número de componentes conexos.
     *
     * @param aristas Vector de aristas del grafo.
     * @param configuracion Vector de pesos asociados a los vértices.
     * @param step Valor de paso para p.
     * @return Un vector de pares donde cada par es un valor de p y el número de componentes conexos.
     */
    vector<tuple<double, int, int, double>> generate_full_percolation(const vector<Edge>& aristas, const vector<double>& configuracion, double step, bool visualization);

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
    vector<bool> nodoActivo;  // Vector que indica si un nodo está activo
    double p_c;  // Valor de p crítico
    int superTop;
    int superBottom;
};

#endif

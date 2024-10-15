#ifndef UNION_FIND_H
#define UNION_FIND_H

#include <vector>
using namespace std;

/**
 * Clase UnionFind (Conjunto Disjunto) para manejar la conectividad dinámica en un grafo.
 * Implementa Union-Find con Path Compression y Union by Size para lograr eficiencia.
 */
class UnionFind {
public:
    /**
     * Constructor que inicializa la estructura de Union-Find.
     * Cada nodo es su propio "padre" (representante) y el tamaño inicial de cada conjunto es 1.
     *
     * @param n Número de nodos (elementos) en el conjunto disjunto.
     */
    UnionFind(int n);

    /**
     * Método find con Path Compression.
     * Encuentra el representante (root) del conjunto al que pertenece el nodo u.
     * Aplica compresión de caminos para optimizar futuras búsquedas.
     *
     * @param u Nodo del que queremos encontrar el representante.
     * @return El representante del conjunto al que pertenece u.
     */
    int find(int u);

    /**
     * Método union con Union by Size.
     * Une dos conjuntos representados por los nodos u y v.
     * El conjunto más pequeño se une al más grande para minimizar la altura del árbol.
     *
     * @param u Nodo del primer conjunto.
     * @param v Nodo del segundo conjunto.
     */
    void unite(int u, int v);

    /**
     * Método que cuenta el número de componentes conexos.
     * Un componente conexo es un conjunto cuyo representante es el mismo nodo.
     *
     * @param n Número de nodos en el grafo.
     * @return El número de componentes conexos.
     */
    int numComponents(int n);

private:
    vector<int> parent;  // Almacena el representante (padre) de cada nodo.
    vector<int> size;    // Almacena el tamaño de cada conjunto.
};

#endif

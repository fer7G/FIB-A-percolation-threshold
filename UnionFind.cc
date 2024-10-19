#include "UnionFind.h"

/**
 * Constructor que inicializa la estructura de Union-Find.
 * Cada nodo es su propio "padre" (representante) y el tamaño inicial de cada conjunto es 1.
 */
UnionFind::UnionFind(int n) {
    parent.resize(n);  // Vector que almacena los representantes de cada nodo.
    size.resize(n, 1); // Vector que almacena el tamaño de cada conjunto.
    for (int i = 0; i < n; ++i) parent[i] = i;  // Inicialmente, cada nodo es su propio padre.
}

/**
 * Método find con Path Compression.
 * Encuentra el representante (root) del conjunto al que pertenece el nodo u.
 * Aplica compresión de caminos para optimizar futuras búsquedas.
 */
int UnionFind::find(int u) {
    if (parent[u] != u)
        parent[u] = find(parent[u]);  // Compresión de caminos.
    return parent[u];
}

/**
 * Método union con Union by Size.
 * Une dos conjuntos representados por los nodos u y v.
 * El conjunto más pequeño se une al más grande para minimizar la altura del árbol.
 */
void UnionFind::unite(int u, int v) {
    int rootU = find(u);
    int rootV = find(v);
    if (rootU != rootV) {
        // Union by size: el conjunto más pequeño se une al más grande.
        if (size[rootU] < size[rootV]) swap(rootU, rootV);
        parent[rootV] = rootU;
        size[rootU] += size[rootV];
    }
}

/**
 * Método que cuenta el número de componentes conexos.
 * Un componente conexo es un conjunto cuyo representante es el mismo nodo.
 */
int UnionFind::numComponents(int n) {
    int count = 0;
    for (int i = 0; i < n; ++i) {
        if (parent[i] == i) ++count;  // Si el nodo es su propio representante, es un componente.
    }
    return count;
}

int UnionFind::get_size(int n) {
    return size[n];
}

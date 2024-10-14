#include <vector>
typedef pair<int, int> Edge;
using namespace std;

class UnionFind {
public:
    vector<int> parent, size;

    UnionFind(int n) {
        parent.resize(n);
        size.resize(n, 1);
        for (int i = 0; i < n; ++i) parent[i] = i;
    }

    int find(int u) {
        if (parent[u] != u)
            parent[u] = find(parent[u]);
        return parent[u];
    }

    void unite(int u, int v) {
        int rootU = find(u);
        int rootV = find(v);
        if (rootU != rootV) {
            if (size[rootU] < size[rootV]) swap(rootU, rootV);
            parent[rootV] = rootU;
            size[rootU] += size[rootV];
        }
    }

    int numComponents(int n) {
        int count = 0;
        for (int i = 0; i < n; ++i) {
            if (parent[i] == i) ++count;
        }
        return count;
    }
};

// Función para percolar el grafo con una configuración y un valor q
int percolarGrafo(int numNodos, const vector<pair<Edge, double>>& configuracion, double q) {
    UnionFind uf(numNodos);

    for (const auto& [arista, peso] : configuracion) {
        if (peso >= q) {  // Si el peso es mayor o igual a q, la arista se mantiene
            uf.unite(arista.first, arista.second);
        }
    }

    return uf.numComponents(numNodos);  // Devuelve el número de componentes conexos
}

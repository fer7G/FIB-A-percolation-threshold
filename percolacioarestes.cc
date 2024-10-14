#include <vector>
#include <iostream>
#include <random>
#include "graph.cpp"
using namespace std;

vector<vector<double>> add_values(Graph g) {
    int sz=g.adjList.size();
    vector<vector<double>> res(sz);
    random_device generador0;
    mt19937 generador(generador0());
    uniform_real_distribution<> distr(0.0,1.0);
    for (int i = 0; i < sz; ++i) {
        for(int j = 0; j < g.adjList[i].size(); ++j) res[i].push_back(distr(generador));
    }
    return res;
}

/*void eraseedge(Graph &g, int x, int vert) {
    int pos = -1;
    int i = 0;
    while (pos == -1) {
        if (g.adjList[x][i]==vert) pos = i;
        ++i;
    }
    g.adjList[x].erase(g[x].begin()+pos);
}

void eraseedge(vector<vector<double>> &g, int x, int vert) {
    int pos = -1;
    int i = 0;
    while (pos == -1) {
        if (g[x][i]==vert) pos = i;
        ++i;
    }
    g[x].erase(g[x].begin()+pos);
}*/

void writegraph(Graph &g, int n) {
    cout << n << endl;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < g.adjList[i].size(); ++j) {
            cout << i << ' ' << g.adjList[i][j] << endl;
            //eraseedge(g,g.adjList[i][j],i);
        }
    }
}

Graph desdobla(const Graph &g) {
    Graph res;
    res.adjList = Matrix(g.adjList.size());
    for (int i = 0; i < g.numNodes; ++i) {
        for (int j = 0; j < g.adjList[i].size(); ++j) {
            res.adjList[i].push_back(g.adjList[i][j]);
            res.adjList[g.adjList[i][j]].push_back(i);
        }
    }
    return res;
}

int percolacio_aristes(Graph g,const double &q,vector<vector<double>> values) {
    int n = g.numNodes;
    double p=1-q;
    for (int i = 0; i < n; ++i) {
        int sz = g.adjList[i].size();
        for (int j = 0; j < sz; ++j) {
            if (values[i][j] < p) {
                g.adjList[i].erase(g.adjList[i].begin()+j);
                values[i].erase(values[i].begin()+j);
            }
        }
    }
    //writegraph(g,n);
    Graph result = desdobla(g);
    return result.connected_components();
}

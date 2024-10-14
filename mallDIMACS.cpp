#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

typedef pair<int, int> Edge;  // Tipo de dato para representar una arista

// Función para generar una malla cuadrada de tamaño n x n
vector<Edge> generarMallaCuadrada(int n) {
    vector<Edge> aristas;

    // Iterar sobre la cuadrícula de tamaño n x n
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            int nodoActual = i * n + j + 1;  // Convertir coordenadas (i, j) a un número de nodo (1-indexado)

            // Conectar con el nodo de la derecha (si existe)
            if (j < n - 1) {
                int nodoDerecha = nodoActual + 1;
                aristas.push_back({nodoActual, nodoDerecha});
            }

            // Conectar con el nodo de abajo (si existe)
            if (i < n - 1) {
                int nodoAbajo = nodoActual + n;
                aristas.push_back({nodoActual, nodoAbajo});
            }
        }
    }

    return aristas;
}

// Función para escribir el grafo en formato DIMACS
void exportarMallaADimacs(int n, const vector<Edge>& aristas, const string& nombreArchivo) {
    ofstream archivo(nombreArchivo);

    if (!archivo.is_open()) {
        cerr << "Error al abrir el archivo!" << endl;
        return;
    }

    int numNodos = n * n;
    int numAristas = aristas.size();

    // Escribir comentario
    archivo << "c Malla cuadrada de tamaño " << n << "x" << n << endl;
    
    // Escribir la línea del problema
    archivo << "p edge " << numNodos << " " << numAristas << endl;

    // Escribir las aristas
    for (const auto& arista : aristas) {
        archivo << "e " << arista.first << " " << arista.second << endl;
    }

    archivo.close();
    cout << "Grafo exportado exitosamente a " << nombreArchivo << endl;
}

int main() {
    int n;
    cout << "Introduce el tamaño de la malla (n): ";
    cin >> n;

    // Generar la malla cuadrada
    vector<Edge> aristas = generarMallaCuadrada(n);

    // Exportar la malla al formato DIMACS
    exportarMallaADimacs(n, aristas, "malla_cuadrada.dimacs");

    return 0;
}

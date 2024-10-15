#include "BondPercolation.h"
#include "SitePercolation.h"
#include "lecturaGrafos.h"
#include <iostream>

using namespace std;

int main() {
    string nombreArchivo;
    cout << "Introduce el nombre del archivo DIMACS: ";
    cin >> nombreArchivo;

    int numNodos;
    vector<Edge> aristas = leerDimacs(nombreArchivo, numNodos);

    if (aristas.empty()) {
        cerr << "Error: No se pudieron leer las aristas del archivo!" << endl;
        return -1;
    }

    int opcion;
    cout << "Elige el tipo de percolación:\n";
    cout << "1. Percolación por aristas\n";
    cout << "2. Percolación por nodos\n";
    cout << "Opción: ";
    cin >> opcion;

    double step;
    cout << "Introduce el valor de step para q (entre 0 y 1): ";
    cin >> step;

    if (opcion == 1) {
        // Percolación por aristas
        BondPercolation percolacion(numNodos);

        // Generar la configuración aleatoria de las aristas
        vector<pair<Edge, double>> configuracion = percolacion.generate_configuration(aristas);

        // Realizar una percolación completa
        vector<pair<double, int>> resultados = percolacion.generate_full_percolation(configuracion, step);

        // Mostrar resultados
        cout << "Resultados de la percolación por aristas completa:\n";
        for (const auto& [q, numComponentes] : resultados) {
            cout << "q = " << q << ", componentes conexos = " << numComponentes << endl;
        }

    } else if (opcion == 2) {
        // Percolación por nodos
        SitePercolation percolacion(numNodos);

        // Generar la configuración aleatoria de los nodos
        vector<double> configuracion = percolacion.generate_configuration();

        // Realizar una percolación completa
        vector<pair<double, int>> resultados = percolacion.generate_full_percolation(aristas, configuracion, step);

        // Mostrar resultados
        cout << "Resultados de la percolación por nodos completa:\n";
        for (const auto& [q, numComponentes] : resultados) {
            cout << "q = " << q << ", componentes conexos = " << numComponentes << endl;
        }

    } else {
        cerr << "Opción no válida" << endl;
        return -1;
    }

    return 0;
}

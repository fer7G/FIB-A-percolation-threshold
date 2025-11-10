#include "BondPercolation.h"
#include "SitePercolation.h"
#include "lecturaGrafos.h"
#include <iostream>
#include <chrono>

using namespace std;

int main() {
    string nombreArchivo;
    cout << "Enter the DIMACS file name: ";
    cin >> nombreArchivo;

    int numNodos;
    vector<Edge> aristas = leerDimacs("../data/" + nombreArchivo, numNodos);

    if (aristas.empty()) {
        cerr << "Error: Could not read edges from file!" << endl;
        return -1;
    }

    int opcion;
    cout << "Choose percolation type:\n";
    cout << "1. Bond percolation\n";
    cout << "2. Site percolation\n";
    cout << "Option: ";
    cin >> opcion;

    double step;
    cout << "Enter the step value for p (between 0 and 1): ";
    cin >> step;

    bool visualization;
    cout << "Do you want to save the position of each node at each step for later visualization? (0 = No, 1 = Yes): ";
    cin >> visualization;

    if (opcion == 1) {
        // Percolación por aristas
        BondPercolation percolacion(numNodos);

        // Generar la configuración aleatoria de las aristas
        vector<pair<Edge, double>> configuracion = percolacion.generate_configuration(aristas);

        // Medir el tiempo de ejecución
        auto start = chrono::high_resolution_clock::now();

        // Realizar una percolación completa
        vector<tuple<double, int, int, double>> resultados = percolacion.generate_full_percolation(configuracion, step, visualization);

        auto end = chrono::high_resolution_clock::now();
        chrono::duration<double> elapsed = end - start;
        cout << "Execution time: " << elapsed.count() << " seconds" << endl;

        // Mostrar encabezado de los resultados con tabs para alineación
        cout << "Complete bond percolation results:\n";
        cout << "p\t\tConnected Components\tSmax\t\tNmax\n";

        // Mostrar resultados
        for (const auto& [p, Ncc, Smax, Nmax] : resultados) {
            cout << p << "\t\t"
                << Ncc << "\t\t\t"
                << Smax << "\t\t"
                << Nmax << endl;
        }

    } else if (opcion == 2) {
        // Percolación por nodos
        SitePercolation percolacion(numNodos);

        // Generar la configuración aleatoria de los nodos
        vector<double> configuracion = percolacion.generate_configuration();

        // Medir el tiempo de ejecución
        auto start = chrono::high_resolution_clock::now();

        // Realizar una percolación completa
        vector<tuple<double, int, int, double>> resultados = percolacion.generate_full_percolation(aristas, configuracion, step, visualization);

        auto end = chrono::high_resolution_clock::now();
        chrono::duration<double> elapsed = end - start;
        cout << "Execution time: " << elapsed.count() << " seconds" << endl;

        // Mostrar encabezado de los resultados con tabs para alineación
        cout << "Complete site percolation results:\n";
        cout << "p\t\tConnected Components\tLargest Cluster Size\tNmax\n";

        // Mostrar resultados
        for (const auto& [p, Ncc, Smax, Nmax] : resultados) {
            cout << p << "\t\t"
                << Ncc << "\t\t\t"
                << Smax << "\t\t\t"
                << Nmax << endl;
        }

    } else {
        cerr << "Invalid option" << endl;
        return -1;
    }

    return 0;
}

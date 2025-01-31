#include "BondPercolation.h"
#include "SitePercolation.h"
#include "lecturaGrafos.h"
#include <iostream>
#include <chrono>

using namespace std;

int main() {
    string nombreArchivo;
    cout << "Introduce el nombre del archivo DIMACS: ";
    cin >> nombreArchivo;

    int numNodos;
    vector<Edge> aristas = leerDimacs("../data/" + nombreArchivo, numNodos);

    if (aristas.empty()) {
        cerr << "Error: No se pudieron leer las aristas del archivo!" << endl;
        return -1;
    }

    int opcion;
    cout << "Elige el tipo de percolación:\n";
    cout << "1. Percolación por aristas\n";
    cout << "2. Percolación por nodos\n";
    cout << "Opción: " << endl;
    cin >> opcion;

    double step;
    cout << "Introduce el valor de step para p (entre 0 y 1): " << endl;
    cin >> step;

    bool visualization;
    cout << "¿Deseas guardar la posición de cada nodo en cada paso para posterior visualización? (0 = No, 1 = Sí): " << endl;
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
        cout << "Tiempo de ejecución: " << elapsed.count() << " segundos" << endl;

        // Mostrar encabezado de los resultados con tabs para alineación
        cout << "Resultados de la percolación por aristas completa:\n";
        cout << "p\t\tComponentes Conexos\tSmax\tNmax\n";

        // Mostrar resultados
        for (const auto& [p, Ncc, Smax, Nmax] : resultados) {
            cout << "p = ";
            cout << p <<", "
                << Ncc << ", "
                << Smax << ", "
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
        cout << "Tiempo de ejecución: " << elapsed.count() << " segundos" << endl;

        // Mostrar encabezado de los resultados con tabs para alineación
        cout << "Resultados de la percolación por nodos completa:\n";
        cout << "p\t\tComponentes Conexos\tTamaño Clúster Mayor\tNmax\n";

        // Mostrar resultados
        for (const auto& [p, Ncc, Smax, Nmax] : resultados) {
            cout << "p = ";
            cout << p <<", "
                << Ncc << ", "
                << Smax << ", "
                << Nmax << endl;
        }

    } else {
        cerr << "Opción no válida" << endl;
        return -1;
    }

    return 0;
}

#include "lecturaGrafos.h"
#include <fstream>
#include <sstream>
#include <iostream>

vector<Edge> leerDimacs(const string& nombreArchivo, int& numNodos) {
    ifstream archivo(nombreArchivo);
    vector<Edge> aristas;
    string linea;

    if (!archivo.is_open()) {
        cerr << "Error al abrir el archivo!" << endl;
        return aristas;
    }

    while (getline(archivo, linea)) {
        if (linea[0] == 'c') {
            // Ignorar líneas de comentario
            continue;
        } else if (linea[0] == 'p') {
            // Leer la línea del problema
            stringstream ss(linea);
            string aux;
            int numAristas;
            ss >> aux >> aux >> numNodos >> numAristas;  // "p edge N M"
        } else if (linea[0] == 'e') {
            // Leer las aristas
            stringstream ss(linea);
            char aux;
            int u, v;
            ss >> aux >> u >> v;
            aristas.push_back({u - 1, v - 1});  // Convertir a 0-indexado
        }
    }

    archivo.close();
    return aristas;
}

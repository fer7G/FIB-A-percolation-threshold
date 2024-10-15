#ifndef LECTURAGRAFOS_H
#define LECTURAGRAFOS_H

#include <vector>
#include <string>
using namespace std;

typedef pair<int, int> Edge;  // Tipo para representar una arista entre dos nodos

// Función para leer un archivo DIMACS y extraer las aristas
vector<Edge> leerDimacs(const string& nombreArchivo, int& numNodos);

#endif
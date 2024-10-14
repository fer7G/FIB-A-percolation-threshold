#include <vector>
#include <cstdlib>
#include <ctime>
#include <utility>

using namespace std;

typedef pair<int, int> Edge; // Representa una arista entre dos nodos (nodo1, nodo2)

// Generar configuración de pesos para las aristas de un grafo
vector<pair<Edge, double>> generarConfiguracion(int numNodos, const vector<Edge>& aristas) {
    vector<pair<Edge, double>> configuracion;
    srand(time(0));  // Inicializar la semilla aleatoria
    
    for (const auto& arista : aristas) {
        double peso = static_cast<double>(rand()) / RAND_MAX;  // Peso aleatorio entre 0 y 1
        configuracion.push_back({arista, peso});
    }

    return configuracion;
}
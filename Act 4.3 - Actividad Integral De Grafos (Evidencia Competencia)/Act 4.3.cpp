#include <iostream>
#include <fstream>
#include <list>
#include <unordered_map>
#include <sstream>

using namespace std;

class Graph {
private:
    unordered_map<string, list<string>> adjList; // Lista de adyacencia con IP como clave y conexiones como valores
    unordered_map<string, int> fanOutCount;      // Contador de fan-out para cada IP
    unordered_map<string, int> segmentFanOut;    // Contador de fan-out para cada segmento

public:
    void addEdge(string sourceIP, string destIP);
    void displayGraph();
    void findFanOut();
};

void Graph::addEdge(string sourceIP, string destIP) {
    adjList[sourceIP].push_back(destIP);
}

void Graph::displayGraph() {
    cout << "Lista de adyacencia:" << endl;
    for (const auto& entry : adjList) {
        cout << entry.first << " -> ";
        for (const auto& dest : entry.second) {
            cout << dest << " ";
        }
        cout << endl;
    }
}

void Graph::findFanOut() {
    int maxFanOut = 0;
    string maxFanOutIP;

    for (const auto& entry : adjList) {
        string segment = entry.first.substr(0, entry.first.rfind('.')); // Obtener el segmento de la IP
        int fanOut = entry.second.size();

        // Actualizar el contador de fan-out para la IP
        fanOutCount[entry.first] = fanOut;

        // Actualizar el contador de fan-out para el segmento
        segmentFanOut[segment] += fanOut;

        cout << "Fan-Out de " << entry.first << ": " << fanOut << endl;

        if (fanOut > maxFanOut) {
            maxFanOut = fanOut;
            maxFanOutIP = entry.first;
        }
    }

    cout << "El nodo con el mayor Fan-Out es: " << maxFanOutIP << " con un Fan-Out de " << maxFanOut << endl;

    // Encontrar el segmento con más fan-out
    int maxSegmentFanOut = 0;
    string maxSegment;
    for (const auto& entry : segmentFanOut) {
        cout << "Fan-Out del segmento " << entry.first << ": " << entry.second << endl;

        if (entry.second > maxSegmentFanOut) {
            maxSegmentFanOut = entry.second;
            maxSegment = entry.first;
        }
    }

    cout << "Segmento con más fan-out: " << maxSegment << ", con: " << maxSegmentFanOut << " aristas o conexiones de salida" << endl;

    // Encontrar la IP del boot master en el segmento con más fan-out
    int maxBootMasterFanOut = 0;
    string bootMasterIP;
    for (const auto& entry : adjList) {
        string segment = entry.first.substr(0, entry.first.rfind('.'));
        if (segment == maxSegment) {
            if (fanOutCount[entry.first] > maxBootMasterFanOut) {
                maxBootMasterFanOut = fanOutCount[entry.first];
                bootMasterIP = entry.first;
            }
        }
    }

    cout << "IP boot master: " << bootMasterIP << " con: " << maxBootMasterFanOut << " fan-outs o conexiones (sumatoria de las conexiones de sus segmentos)" << endl;
}

int main() {
    ifstream file("Bitacora.txt");
    string line;
    Graph g;

    while (getline(file, line)) {
        // Analizar la línea y extraer la información necesaria
        stringstream ss(line);
        string month, day, time, ip, reason;
        ss >> month >> day >> time >> ip >> reason;

        // Agregar la conexión al grafo
        g.addEdge(ip, reason);
    }

    // Mostrar el grafo y encontrar el Fan-Out
    g.displayGraph();
    g.findFanOut();

    return 0;
}



//g++ "Act 4.3.cpp" -o "Act 4.3" -std=c++11

//./"Act 4.3"
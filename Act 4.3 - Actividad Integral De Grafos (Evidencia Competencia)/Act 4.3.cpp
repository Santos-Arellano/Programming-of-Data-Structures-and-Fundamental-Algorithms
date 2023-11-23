#include <iostream>
#include <fstream>
#include <list>
#include <unordered_map>
#include <sstream>
#include <stdexcept>

using namespace std;

class Graph {
private:
    unordered_map<string, list<string>> adjList;
    mutable unordered_map<string, int> fanOutCount;   // Ahora es mutable
    mutable unordered_map<string, int> segmentFanOut; // Ahora es mutable

public:
    void addEdge(const string& sourceIP, const string& destIP);
    void displayGraph() const;
    void findFanOut() const;
};

void Graph::addEdge(const string& sourceIP, const string& destIP) {
    adjList[sourceIP].push_back(destIP);
}

void Graph::displayGraph() const {
    cout << "Lista de adyacencia:" << endl;
    for (const auto& entry : adjList) {
        cout << entry.first << " -> ";
        for (const auto& dest : entry.second) {
            cout << dest << " ";
        }
        cout << endl;
    }
}

void Graph::findFanOut() const {
    int maxFanOut = 0;
    string maxFanOutIP;

    for (const auto& entry : adjList) {
        string segment = entry.first.substr(0, entry.first.rfind('.'));
        int fanOut = entry.second.size();

        fanOutCount[entry.first] = fanOut;
        segmentFanOut[segment] += fanOut;

        cout << "Fan-Out de " << entry.first << ": " << fanOut << endl;

        if (fanOut > maxFanOut) {
            maxFanOut = fanOut;
            maxFanOutIP = entry.first;
        }
    }

    cout << "El nodo con el mayor Fan-Out es: " << maxFanOutIP << " con un Fan-Out de " << maxFanOut << endl;

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
    try {
        ifstream file("Bitacora.txt");
        if (!file.is_open()) {
            throw runtime_error("Error al abrir el archivo");
        }

        string line;
        Graph g;

        while (getline(file, line)) {
            stringstream ss(line);
            string month, day, time, ip, reason;
            ss >> month >> day >> time >> ip >> reason;

            g.addEdge(ip, reason);
        }

        g.displayGraph();
        g.findFanOut();
    } catch (const exception& e) {
        cerr << "Error: " << e.what() << endl;
        return 1;
    }

    return 0;
}



//g++ "Act 4.3.cpp" -o "Act 4.3" -std=c++11

//./"Act 4.3"
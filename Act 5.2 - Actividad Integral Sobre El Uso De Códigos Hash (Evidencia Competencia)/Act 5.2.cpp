#include <iostream>
#include <fstream>
#include <sstream>
#include "HashTable.h"

using namespace std;

int main() {
    // Crear un objeto de la clase LogAnalyzer
    LogAnalyzer logAnalyzer;

    // Procesar el archivo de bitácora
    logAnalyzer.processLogFile("bitacora.txt");

    // Crear un objeto de la clase HashTable con un tamaño arbitrario (en este caso, 10)
    HashTable hashTable(10);

    // Abrir el archivo de bitácora
    ifstream logFile("bitacora.txt");
    if (!logFile.is_open()) {
        cerr << "Error opening file: bitacora.txt" << endl;
        return 1;
    }

    string line;
    while (getline(logFile, line)) {
        // Procesar cada entrada del archivo de bitácora e insertarla en la tabla hash
        hashTable.processLogEntry(line);
    }

    logFile.close();

    // Imprimir información sobre un dominio específico (cambia "example.com" por el dominio que desees)
    hashTable.print("example.com");

    return 0;
}

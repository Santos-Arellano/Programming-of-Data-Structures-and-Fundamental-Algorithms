#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "HashTable.h"

using namespace std;

string extractIp(string &line) {
    string mes, dia, hora, ip;
    stringstream extract(line);
    extract >> mes >> dia >> hora >> ip;
    return ip;
}

long long stringToLongIP(const string& full_ip) {
    size_t colonPos = full_ip.find(":");
    if (colonPos != string::npos) {
        string ip = full_ip.substr(0, colonPos);
        string puerto = full_ip.substr(colonPos + 1);

        // Convertir cada parte de la IP a entero y concatenarlas
        stringstream ip_stream(ip);
        int ip_part;
        string ip_concatenada;
        for (int i = 0; i < 4; i++) {
            ip_stream >> ip_part;
            ip_concatenada += to_string(ip_part);
            if (i < 3) {
                // Añadir un separador entre las partes de la IP
                ip_concatenada += ".";
            }
        }

        // Concatenar la IP y el puerto
        ip_concatenada += ":" + puerto;

        // Convertir la IP completa a long long
        long long ip_int = stoll(ip_concatenada);
        return ip_int;
    }
    return 0;
}

int main() {
    HashTable hashTable;

    ifstream inputFile("bitacora.txt");
    if (!inputFile.is_open()) {
        cerr << "Error al abrir el archivo.\n";
        return 1;
    }

    string line;
    while (getline(inputFile, line)) {
        string ip = extractIp(line);
        long long ips = stringToLongIP(ip);
        hashTable.insert(ips, line);

    }
    inputFile.close();
    hashTable.insert(3114984089,"Sep 24 17:22:12 311.49.840.89:4145 Failed password for illegal user guest");
    // Imprimir datos para una IP específica
    hashTable.print(3114984089);

    return 0;
}

/*
g++ -c LinkedList.cpp -o LinkedList.o
g++ -c HashTable.cpp -o HashTable.o
g++ -c main.cpp -o main.o
g++ main.o HashTable.o LinkedList.o -o main

*/

//./main
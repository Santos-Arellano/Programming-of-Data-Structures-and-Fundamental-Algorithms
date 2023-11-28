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
            stringstream f(ip);
            string ip_num, resultado;
            for (int i = 0; i < 4; i++) {
                getline(f, ip_num, '.');
                resultado = resultado + ip_num;
            }
            resultado = resultado + puerto;
            long long ip_int = stoll(resultado);
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
    //hashTable.insert(3114984089,"Sep 24 17:22:12 311.49.840.89:4145 Failed password for illegal user guest");
    //hashTable.print(3114984089);
    string ip_;
    cout << "¿De cuál IP quieres obtener su resumen? (ejemplo:311.49.840.89:4145)" << endl;
    cin>>ip_;
    hashTable.print(stringToLongIP(ip_));
    return 0;
}


/*
g++ -c LinkedList.cpp -o LinkedList.o
g++ -c HashTable.cpp -o HashTable.o
g++ -c main.cpp -o main.o
g++ main.o HashTable.o LinkedList.o -o main
./main

*/
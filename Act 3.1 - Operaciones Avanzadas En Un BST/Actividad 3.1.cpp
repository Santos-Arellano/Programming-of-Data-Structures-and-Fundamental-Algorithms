#include <iostream>
#include <fstream>
#include <string>
using namespace std;

class bitacoraEntrada {
public:
    string mes;
    int dia;
    string fecha;
    string ipAdress;
    string razon;
    bitacoraEntrada* next;
    bitacoraEntrada* prev;

    bitacoraEntrada(string m, int d, string t, string ip, string r);
};

bitacoraEntrada::bitacoraEntrada(string m, int d, string t, string ip, string r) {
    mes = m;
    dia = d;
    fecha = t;
    ipAdress = ip;
    razon = r;
    next = nullptr;
    prev = nullptr;
}

class bitacoraLista {
public:
    bitacoraEntrada* head;
    bitacoraEntrada* tail;

    bitacoraLista() : head(nullptr), tail(nullptr) {}

    void addOrderedEntry(string m, int d, string t, string ip, string r) {
        bitacoraEntrada* newEntry = new bitacoraEntrada(m, d, t, ip, r);

        if (!head) {
            head = tail = newEntry;
        } else {
            bitacoraEntrada* current = head;

            while (current && ip > current->ipAdress) {
                current = current->next;
            }

            if (!current) {
                newEntry->prev = tail;
                tail->next = newEntry;
                tail = newEntry;
            } else if (current == head) {
                newEntry->next = head;
                head->prev = newEntry;
                head = newEntry;
            } else {
                newEntry->next = current;
                newEntry->prev = current->prev;
                current->prev->next = newEntry;
                current->prev = newEntry;
            }
        }
    }

    void DisplayEntries(string startIP, string endIP) {
    bitacoraEntrada* current = head;

    while (current) {
        if (current->ipAdress >= startIP && current->ipAdress <= endIP) {
            cout << "Mes: " << current->mes << endl;
            cout << "Dia: " << current->dia << endl;
            cout << "Fecha: " << current->fecha << endl;
            cout << "IP: " << current->ipAdress << endl;
            cout << "Razon: " << current->razon << endl;
            cout << "----------------------" << endl;
        }
        current = current->next;
    }
}

    void saveOrderedDataToFile(const string& filename) {
        ofstream outputFile(filename);
        bitacoraEntrada* current = head;

        while (current != nullptr) {
            outputFile << current->mes << " " << current->dia << " " << current->fecha << " " << current->ipAdress << " " << current->razon << endl;
            current = current->next;
        }

        outputFile.close();
    }

    ~bitacoraLista() {
        bitacoraEntrada* current = head;
        while (current != nullptr) {
            bitacoraEntrada* temp = current;
            current = current->next;
            delete temp;
        }
    }
};

int main() {
    ifstream inputFile("bitacora.txt");
    if (!inputFile.is_open()) {
        cerr << "Error: No se pudo abrir el archivo." << endl;
        return 1;
    }

    bitacoraLista logList;
    string mes, fecha, ipAdress, razon;
    int dia;

    while (inputFile >> mes >> dia >> fecha >> ipAdress) {
        getline(inputFile, razon);
        razon = razon.substr(1);
        logList.addOrderedEntry(mes, dia, fecha, ipAdress, razon);
    }

    inputFile.close();

    string startIP, endIP;
    cout << "Inicio de la busqueda del IP: ";
    cin >> startIP;
    cout << "Final de la busqueda del IP: ";
    cin >> endIP;

    logList.DisplayEntries(startIP, endIP);
    logList.saveOrderedDataToFile("ordenadas.txt");

    return 0;
}
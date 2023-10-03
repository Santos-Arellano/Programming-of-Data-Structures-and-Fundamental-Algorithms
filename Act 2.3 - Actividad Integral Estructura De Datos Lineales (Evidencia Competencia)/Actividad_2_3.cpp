#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <unordered_map>
#include <stdexcept> 
using namespace std;

// Definición de una estructura de nodo para una lista doblemente enlazada
struct Node {
    long long data; // Almacena datos de tipo long long (para direcciones IP)
    Node* next;     // Puntero al siguiente nodo
    Node* previous; // Puntero al nodo anterior
};

// Definición de una clase para una lista doblemente enlazada
class dLinkedList {
public:
    Node* head; // Puntero al primer nodo
    Node* tail; // Puntero al último nodo
    dLinkedList(); // Constructor
    ~dLinkedList(); // Destructor para liberar memoria
    void push(long long); // Método para agregar un nodo al inicio de la lista
};

// Constructor de la lista doblemente enlazada
dLinkedList::dLinkedList() {
    head = nullptr;
    tail = nullptr;
}

// Destructor de la lista doblemente enlazada para liberar memoria de nodos
dLinkedList::~dLinkedList() {
    while (head != nullptr) {
        Node* temp = head;
        head = head->next;
        delete temp;
    }
}

// Método para agregar un nodo al inicio de la lista
void dLinkedList::push(long long data) {
    Node* new_node = new Node;
    new_node->data = data;
    new_node->next = nullptr;
    new_node->previous = nullptr;
    if (head == nullptr && tail == nullptr) {
        new_node->next = head;
        new_node->previous = nullptr;
        head = new_node;
        tail = new_node;
    }
    else {
        new_node->next = head;
        head->previous = new_node;
        head = new_node;
        new_node->previous = nullptr;
    }
}

// Función para lanzar una excepción con un mensaje de error
void throwError(const string& errorMessage) {
    throw runtime_error(errorMessage);
}

// Función para abrir un archivo en modo lectura y manejar errores
ifstream openFileForReading(const string& fileName) {
    ifstream file(fileName);
    if (!file.is_open()) {
        throwError("Error: No se pudo abrir el archivo '" + fileName + "'.");
    }
    return file;
}

// Función para abrir un archivo en modo escritura y manejar errores
ofstream openFileForWriting(const string& fileName) {
    ofstream file(fileName);
    if (!file.is_open()) {
        throwError("Error: No se pudo abrir el archivo '" + fileName + "'.");
    }
    return file;
}

// Función para ordenar un vector usando el algoritmo de Merge Sort
void ordenaMerge(vector<long long int>& a, int low, int high) {
    if (low < high) {
        int mid = low + (high - low) / 2;
        ordenaMerge(a, low, mid);
        ordenaMerge(a, mid + 1, high);
        vector<long long int> res(high - low + 1);
        int i = low;
        int j = mid + 1;
        int k = 0;
        while (i <= mid && j <= high) {
            if (a[i] <= a[j]) {
                res[k] = a[i];
                i += 1;
            }
            else {
                res[k] = a[j];
                j += 1;
            }
            k += 1;
        }
        while (i <= mid) {
            res[k] = a[i];
            i += 1;
            k += 1;
        }
        while (j <= high) {
            res[k] = a[j];
            j += 1;
            k += 1;
        }
        for (int h = 0; h <= high - low; h++) {
            a[low + h] = res[h];
        }
    }
}

// Función para convertir una dirección IP en formato de cadena a un número long long
long long stringToLongIP(const string& full_ip) {
    try {
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
        else {
            throwError("Error: El formato de la dirección IP no es válido.");
            return 0;
        }
    }
    catch (const std::invalid_argument& e) {
        throwError("Error: Dirección IP no válida.");
        return 0;
    }
}

// Función para realizar una búsqueda binaria en la lista doblemente enlazada
Node* binarySearch(Node* tail, Node* head, long long key, long long low, long long high) {
    long long diferencia_kt = abs(key - tail->data);
    long long diferencia_kh = abs(key - head->data);
    Node* current_node;
    int comienzo = -1;
    if (diferencia_kh < diferencia_kt) {
        current_node = head;
        comienzo = 1;
    }
    else if (diferencia_kh == diferencia_kt) {
        current_node = head;
        comienzo = 1;
    }
    else {
        current_node = tail;
        comienzo = 0;
    }
    if (low <= high) {
        long long mid = (low + high) / 2;
        if (comienzo == 1) {
            for (long long i = 0; i < mid; i++) {
                current_node = current_node->next;
            }
            if (key == current_node->data) {
                return current_node;
            }
            else if (key > current_node->data) {
                high = mid - 1LL;
                return binarySearch(tail, head, key, low, high);
            }
            else {
                low = mid + 1LL;
                return binarySearch(tail, head, key, low, high);
            }
        }
        else {
            for (long long i = 0; i < mid; i++) {
                current_node = current_node->previous;
            }
            if (key == current_node->data) {
                return current_node;
            }
            else if (key > current_node->data) {
                low = mid + 1LL;
                return binarySearch(tail, head, key, low, high);
            }
            else {
                high = mid - 1LL;
                return binarySearch(tail, head, key, low, high);
            }
        }
    }
    else {
        return nullptr;
    }
}

// Función para almacenar una línea en un archivo
void storeInTxt(const string& line, ofstream& archivo) {  
    if (archivo.is_open()) {
        archivo << line << endl;
    } else {
        throwError("Error al escribir en el archivo.");
    }
}

// Función principal para leer, almacenar, ordenar y buscar direcciones IP
void leerAlmacenarOrdenar(const string& l, const string& r) {
    ifstream bitacora = openFileForReading("bitacora.txt");
    unordered_map<long long int, string> infoMap;
    string line;
    vector<long long int> Ip_Desordenadas;
    string mes, dia, hora, ip, fallo;

    while (getline(bitacora, line)) {
        stringstream iss(line);
        iss >> mes >> dia >> hora >> ip;
        size_t colonPos = ip.find(':');
        if (colonPos != string::npos) {
            string puerto = ip.substr(colonPos);
            ip = ip.substr(0, colonPos);
            ip += puerto;
        }
        getline(iss, fallo);
        string fecha = mes + " " + dia + " " + hora;
        long long int key = stringToLongIP(ip);
        infoMap[key] = line;
        Ip_Desordenadas.push_back(key);
    }

    ordenaMerge(Ip_Desordenadas, 0, Ip_Desordenadas.size() - 1);
    dLinkedList lista;

    for (long long key : Ip_Desordenadas) {
        lista.push(key);
    }

    long long int ipInicio = stringToLongIP(l);
    long long int ipFinal = stringToLongIP(r);

    Node* inicio_busqueda = binarySearch(lista.tail, lista.head, ipInicio, 0, Ip_Desordenadas.size() - 1);
    Node* final_busqueda = binarySearch(lista.tail, lista.head, ipFinal, 0, Ip_Desordenadas.size() - 1);

    ofstream archivo = openFileForWriting("rango.txt");

    if (inicio_busqueda != nullptr && final_busqueda != nullptr) {
        Node* current_node = inicio_busqueda;
        cout << "Las IP han sido encontradas:" << endl;

        while (current_node != final_busqueda->previous) {
            line = infoMap[current_node->data];
            cout << "Forma 1: " << line << endl;
            storeInTxt(line, archivo);
            current_node = current_node->previous;
        }
    } else {
        vector<string> rango_fechas;
        cout << "Las IP no han sido encontradas, pero se muestra el rango a partir de las IPs proporcionadas:" << endl;

        for (long long int i : Ip_Desordenadas) {
            if (i >= ipInicio && i <= ipFinal) {
                long long int key = i;
                auto it = infoMap.find(key);
                rango_fechas.push_back(it->second);
                cout << "Forma 2: " << it->second << endl;
                storeInTxt(it->second, archivo);
            }
        }

        if (rango_fechas.empty()) {
            cout << "No se encontraron registros en el rango especificado." << endl;
        }
    }

    bitacora.close();
    archivo.close();
}

// Función principal del programa
int main() {
    cout << "Elige una IP de inicio y final (con números) para la búsqueda: " << endl;
    cout << "Ejemplo: ###.##.###.###:####" << endl;
    string inicio, final;
    getline(cin, inicio);
    getline(cin, final);

    try {
        leerAlmacenarOrdenar(inicio, final);
    } catch (const exception& e) {
        cerr << e.what() << endl;
    }

    return 0;
}

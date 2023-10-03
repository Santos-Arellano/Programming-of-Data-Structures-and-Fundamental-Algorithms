#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <unordered_map>
#include <stdexcept>
using namespace std;

// Definición de la estructura Node para la lista doblemente enlazada
struct Node {
    long long data;
    Node* next;
    Node* previous;
};

// Definición de la clase dLinkedList para la lista doblemente enlazada
class dLinkedList {
public:
    Node* head;
    Node* tail;
    dLinkedList();
    ~dLinkedList();
    void push(long long);
};

// Constructor de la clase dLinkedList
dLinkedList::dLinkedList() {
    head = nullptr;
    tail = nullptr;
}

// Destructor de la clase dLinkedList
dLinkedList::~dLinkedList() {
    while (head != nullptr) {
        Node* temp = head;
        head = head->next;
        delete temp;
    }
}

// Método para agregar un elemento al principio de la lista
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

// Función para realizar la ordenación Merge Sort en un vector
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

// Función para convertir una dirección IP de formato string a entero long long
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
            cerr << "Error: El formato de la dirección IP no es válido." << endl;
            return 0;
        }
    }
    catch (const std::invalid_argument& e) {
        cerr << "Error: Dirección IP no válida." << endl;
        return 0;
    }
}

// Función de búsqueda binaria en la lista doblemente enlazada
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

// Función para leer, almacenar y ordenar los datos de la bitácora
void leerAlmacenarOrdenar(const string& l, const string& r) {
    ifstream bitacora;
    bitacora.open("bitacora.txt", ios::in);
    if (bitacora.fail()) {
        cerr << "Error: No se pudo abrir el archivo 'bitacora.txt'." << endl;
    }
    else {
        // Mapa no ordenado para almacenar información de IP y líneas correspondientes
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
        // Llamada a la función de ordenación Merge Sort
        ordenaMerge(Ip_Desordenadas, 0, Ip_Desordenadas.size() - 1);
        dLinkedList lista;
        for (long long key : Ip_Desordenadas) {
            lista.push(key);
        }
        long long int ipInicio = stringToLongIP(l);
        long long int ipFinal = stringToLongIP(r);
        Node* inicio_busqueda = binarySearch(lista.tail, lista.head, ipInicio, 0, Ip_Desordenadas.size() - 1);
        Node* final_busqueda = binarySearch(lista.tail, lista.head, ipFinal, 0, Ip_Desordenadas.size() - 1);

        ofstream resultados("resultados.txt"); // Abrir un archivo para escribir los resultados

        if (resultados.is_open()) {
            if (inicio_busqueda != nullptr && final_busqueda != nullptr) {
                Node* current_node = inicio_busqueda;
                resultados << "Las IP han sido encontradas:" << endl;
                while (current_node != final_busqueda->previous) {
                    resultados << "Forma 1: " << infoMap[current_node->data] << endl;
                    current_node = current_node->previous;
                }
            }
            else {
                vector<string> rango_fechas;
                resultados << "Las IP no han sido encontradas, pero se muestra el rango a partir de las IPs proporcionadas:" << endl;
                for (long long int i : Ip_Desordenadas) {
                    if (i >= ipInicio && i <= ipFinal) {
                        long long int key = i;
                        auto it = infoMap.find(key);
                        rango_fechas.push_back(it->second);
                        resultados << "Forma 2: " << it->second << endl;
                    }
                }
                if (rango_fechas.empty()) {
                    resultados << "No se encontraron registros en el rango especificado." << endl;
                }
            }

            resultados.close(); // Cerrar el archivo de resultados

            cout << "Los resultados se han guardado en 'resultados.txt'." << endl;
        }
        else {
            cerr << "Error: No se pudo abrir el archivo de resultados." << endl;
        }

        bitacora.close();
    }
}

int main() {
    cout << "Elige una IP de inicio y final (con números) para la búsqueda: " << endl;
    cout << "Ejemplo: ###.##.###.###:####" << endl;
    string inicio, final;
    getline(cin, inicio);
    getline(cin, final);
    leerAlmacenarOrdenar(inicio, final);
    return 0;
}

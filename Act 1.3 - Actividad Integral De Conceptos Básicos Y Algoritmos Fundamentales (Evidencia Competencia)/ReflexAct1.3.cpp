/*
El formato del archivo “bitacora.txt” es el siguiente:
• Mes en formato de 3 letras.
• Día
• Hora en formato hh:mm:ss
• Dirección IP origen en formato ###.##.###.###:####
• Razón de la falla.
Ejemplo:
Aug 4 03:18:56 960.96.3.29:5268 Failed password for admin

Donde indica que el 4 de Agosto a las 3 de la mañana con 18
minutos y 56 segundos hubo un acceso fallido la cuenta de admin
por error de password y llego de la dirección IP 960.96.3.29 puerto
5268.
*/

#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <algorithm>
using namespace std;

// Definición de la estructura para almacenar los datos
struct inputData { // Estructura para almacenar los datos
    int key;            // Clave calculada a partir de mes y día
    string month, time, ip, concept;
    int day;
};

// Función para dividir una cadena en tokens usando un delimitador
vector<string> splitString(string text, string delimiter) {
    vector<string> tokens; // Vector para almacenar los tokens resultantes de la división
    size_t current = text.find(delimiter); // Encontrar el primer delimitador en la cadena
    size_t previous = 0;
    while (current != string::npos) {
        tokens.push_back(text.substr(previous, current - previous));
        previous = current + 1;
        current = text.find(delimiter, previous);
    }
    tokens.push_back(text.substr(previous, current - previous));
    return tokens;
}

// Función para calcular la clave a partir del mes y día
int getKey(string month, int day) {
    int keyValue = 0;
    if (month == "Jan") keyValue = 100 + day;
    if (month == "Feb") keyValue = 200 + day;
    if (month == "Mar") keyValue = 300 + day;
    if (month == "Apr") keyValue = 400 + day;
    if (month == "May") keyValue = 500 + day;
    if (month == "Jun") keyValue = 600 + day;
    if (month == "Jul") keyValue = 700 + day;
    if (month == "Aug") keyValue = 800 + day;
    if (month == "Sep") keyValue = 900 + day;
    if (month == "Oct") keyValue = 1000 + day;
    if (month == "Nov") keyValue = 1100 + day;
    if (month == "Dec") keyValue = 1200 + day;
    return keyValue;

}

// Función para leer el archivo de entrada y almacenar los datos en el vector
void readFile(vector<inputData>& vecOfStrs) {
  string filename = "bitacora.txt";
    string str;
    ifstream in(filename);
    if (in) {
        while (getline(in, str)) {
            vector<string> e = splitString(str, " ");
            inputData input;
            input.key = getKey(e[0], stoi(e[1]));
            input.month = e[0];
            input.day = stoi(e[1]);
            input.time = e[2];
            input.ip = e[3];
            string problem;
            for (int i = 4; i < e.size(); i++) {
                problem += e[i] + " ";
            }
            input.concept = problem;
            if (str.size() > 0) {
                vecOfStrs.push_back(input);
            }
        }
    }
    in.close();
}

// Función auxiliar para comparar dos elementos por su clave
bool compareKey(const inputData& a, const inputData& b) {
    return a.key < b.key;
}

// Función para buscar la posición de un elemento en el vector a partir de su clave
int intervalSearch(vector<inputData>& vecOfStrs, int date) {
    for (int i = 0; i < vecOfStrs.size(); i++) {
        if (vecOfStrs[i].key >= date) {
            return i;
        }
    }
    return -1;
}

// Función para escribir los registros en un rango en el archivo de salida
void outputInterval(vector<inputData>& vecOfStrs, int start, int end) {
    ofstream outputFile;
    outputFile.open("output.txt");
    for (int i = start; i < end; i++) {
        outputFile << vecOfStrs[i].month << " " << vecOfStrs[i].day << " " <<
            vecOfStrs[i].time << " " << vecOfStrs[i].ip << " " << vecOfStrs[i].concept <<
            endl;
    }
    outputFile.close(); // Es importante cerrar el archivo después de escribir
}

// Función para validar si una cadena es un entero válido
bool esEnteroValido(const string& str) {
    try {
        stoi(str);
        return true;
    } catch (const std::invalid_argument& e) {
        return false;
    }
}

int main() {
    int start, end, startDateKey, endDateKey;
    string startInput, endInput;
    vector<inputData> vecOfStrs;
    readFile(vecOfStrs);
    sort(vecOfStrs.begin(), vecOfStrs.end(), compareKey);
    
    // Obtener la fecha de inicio del usuario
    cout << "Ingresa la fecha de inicio (m/dd , Ej: Jun 10): " << endl;
    getline(cin, startInput);
    vector<string> startVector = splitString(startInput, " ");
    if (startVector.size() == 2) {
        if (esEnteroValido(startVector[1])) {
            int startDay = stoi(startVector[1]); // Convertir solo el día a entero
            startDateKey = getKey(startVector[0], startDay);
        } else {
            cout << "Día no válido. Por favor ingresa un entero válido." << endl;
            return 1; // Salir con un código de error
        }
    } else {
        cout << "Formato de entrada no válido. Por favor usa el formato 'm/dd'." << endl;
        return 1; // Salir con un código de error
    }

    // Obtener la fecha de fin del usuario
    cout << "Ingresa la fecha de fin (m/dd): " << endl;
    getline(cin, endInput);
    vector<string> endVector = splitString(endInput, " ");
    if (endVector.size() == 2) {
        if (esEnteroValido(endVector[1])) {
            int endDay = stoi(endVector[1]); // Convertir solo el día a entero
            endDateKey = getKey(endVector[0], endDay);
        } else {
            cout << "Día no válido. Por favor ingresa un entero válido." << endl;
            return 1; // Salir con un código de error
        }
    } else {
        cout << "Formato de entrada no válido. Por favor usa el formato 'm/dd'." << endl;
        return 1; // Salir con un código de error
    }

    // Buscar los índices de inicio y fin en el vector
    start = intervalSearch(vecOfStrs, startDateKey);
    end = intervalSearch(vecOfStrs, endDateKey + 1);

    // Escribir los registros en el archivo de salida
    outputInterval(vecOfStrs, start, end);

    return 0; // Todo funcionó correctamente
}

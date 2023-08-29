//Buscar Con La Busqueda Secuencial Un Dato Entero Dentro Del Vector.

#include <iostream>

using namespace std;

int BusqSecuencial(int arr[], int key, int low, int high) {
    while (low <= high) {
        if (key == arr[low]) {
            return low;
        } else if (key < arr[low]) {
            high = low - 1;
        } else {
            low = low + 1; 
        }
    }
    return -1;
}

int main(){ 
    int arr[] = {1, 2, 3, 4, 5, 6, 7, 8}; 
    int low = 0; 
    int high = sizeof(arr) / sizeof(arr[0]) - 1;
    int key;
    cout << "que numero quieres buscar desde "<< arr[low] << " hasta " << arr[high] << endl;
    cout << "Dame el número para que deseas buscar: ";
    cin >> key;
    int result = BusqSecuencial(arr, key, low, high);
    if (result == -1) {
        cout << "El elemento no se encuentra en el arreglo" << endl;
    } else {
        cout << "El elemento se encuentra en la posicion: " << result << endl;
    }
    return 0;
}
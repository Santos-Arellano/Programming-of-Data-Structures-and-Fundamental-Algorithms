/*Buscar Con La Busqueda Binaria Un Dato Entero Dentro Del Vector de forma recursiva.*/

#include <iostream>

using namespace std;

int BusqBinariaRecursiva(int arr[], int key, int low, int high) { 
    if (low > high) { 
        return -1;
    }
    int mid = low + (high - low) / 2;
    if (key == arr[mid]) { 
        return mid;
    } else if (key < arr[mid]) { 
        return BusqBinariaRecursiva(arr, key, low, mid - 1);
    } else {
        return BusqBinariaRecursiva(arr, key, mid + 1, high); 
    }
}

int main() {
    int arr[] = {1, 2, 3, 4, 5, 6, 7, 8}; 
    int low = 0; 
    int high = sizeof(arr) / sizeof(arr[0]) - 1;
    int key;
    cout << "que numero quieres buscar desde "<< arr[low] << " hasta " << arr[high] << endl;
    cout << "Dame el número para que deseas buscar: ";
    cin >> key;
    int result = BusqBinariaRecursiva(arr, key, low, high);
    if (result == -1) {
        cout << "El elemento no se encuentra en el arreglo" << endl;
    } else {
        cout << "El elemento se encuentra en la posicion: " << result << endl;
    }
    return 0;
}

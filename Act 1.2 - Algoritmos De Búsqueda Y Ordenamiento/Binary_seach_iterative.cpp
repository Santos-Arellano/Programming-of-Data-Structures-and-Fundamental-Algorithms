/*Buscar Con La Busqueda Binaria Un Dato Entero Dentro Del Vector de forma iterativa.*/

#include <iostream>

using namespace std;

int BusqBinariaIterativa(int arr[], int key, int low, int high) { //Aqui se declara la funcion
    while (low <= high) { //Mientras que el valor de low sea menor o igual al valor de high
        int mid = low + (high - low) / 2; //Se declara la variable mid que es igual a low + (high - low) / 2
        if (key == arr[mid]) { //Si el valor de key es igual al valor de arr[mid] entonces se regresa el valor de mid
            return mid;
        } else if (key < arr[mid]) { //Si el valor de key es menor al valor de arr[mid] entonces se le resta 1 a mid
            high = mid - 1; //Y se le asigna el valor a high 
        } else {
            low = mid + 1;  //Si no se cumple ninguna de las condiciones anteriores entonces se le suma 1 a mid
        }
    }
    return -1;
}

int main(){
    int arr[] = {1, 2, 3, 4, 5, 6, 7, 8};  //Se declara el arreglo
    int low = 0;  
    int high = sizeof(arr) / sizeof(arr[0]) - 1; //Se declara la variable high que es igual al tamaño del arreglo entre el tamaño de un entero menos 1
    int key;
    cout << "que numero quieres buscar desde "<< arr[low] << " hasta " << arr[high] << endl; //Se le pide al usuario que ingrese el numero que desea buscar
    cout << "Dame el número para que deseas buscar: ";
    cin >> key;
    int result = BusqBinariaIterativa(arr, key, low, high);
    if (result == -1) {
        cout << "El elemento no se encuentra en el arreglo" << endl;
    } else {
        cout << "El elemento se encuentra en la posicion: " << result << endl;
    }
    return 0;
}


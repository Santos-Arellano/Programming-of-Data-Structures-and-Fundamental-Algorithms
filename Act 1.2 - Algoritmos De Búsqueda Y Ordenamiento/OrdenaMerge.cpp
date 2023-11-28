//Ordene En Forma Ascendente Los Datos Con El Método De Merge

#include <iostream>

using namespace std;

void Merge(int arr[], int low, int mid, int high) { 
    int i, j, k, c[50];
    i = low;
    k = low;
    j = mid + 1;
    while (i <= mid && j <= high) { 
        if (arr[i] < arr[j]) {
            c[k] = arr[i];
            k++;
            i++;
        } else {
            c[k] = arr[j]; 
            k++;
            j++;
        }
    }
    while (i <= mid) {
        c[k] = arr[i];
        k++;
        i++;
    }
    while (j <= high) {
        c[k] = arr[j];
        k++;
        j++;
    }
    for (i = low; i < k; i++) {
        arr[i] = c[i];
    }
}

void MergeSort(int arr[], int low, int high) {
    int mid;
    if (low < high) {
        mid = (low + high) / 2;
        MergeSort(arr, low, mid);
        MergeSort(arr, mid + 1, high);
        Merge(arr, low, mid, high);
    }
}

int main() {
    int arr[] = {8, 7, 6, 5, 4, 3, 2, 1};
    int low = 0;
    int high = sizeof(arr) / sizeof(arr[0]) - 1;
    MergeSort(arr, low, high);
    cout << "El arreglo ordenado es: ";
    for (int i = 0; i <= high; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
}


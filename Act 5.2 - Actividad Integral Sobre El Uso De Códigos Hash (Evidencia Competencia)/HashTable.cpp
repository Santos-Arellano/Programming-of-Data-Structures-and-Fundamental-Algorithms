#include "HashTable.h"

HashTable::HashTable() {
    cout << "¿Cuántos datos tienes?" << endl;
    cin >> cant_datos;
    cout << "¿En cuántos buckets quieres que se almacenen?" << endl;
    cin >> size;

    array = new Buckets[size];
    int bucket_key = 0;

    for (int i = 0; i < size; i++) {
        array[i].key = bucket_key;
        bucket_key += (cant_datos / size);
        if (i < (cant_datos % size)) {
            bucket_key += 1;
        }
    }
}

HashTable::~HashTable() {
    delete[] array;
}

void HashTable::insert(int key, int value) {
    for (int i = 0; i < size; i++) {
        if (array[i].key == key) {
            array[i].list.push(value);
        }
    }
}

void HashTable::remove(int key) {
    for (int i = 0; i < size; i++) {
        if (array[i].key == key) {
            array[i].list.del();
        }
    }
}

void HashTable::print(int key) {
    // Implementa la lógica para imprimir el contenido de la lista correspondiente al bucket con la clave 'key'
}

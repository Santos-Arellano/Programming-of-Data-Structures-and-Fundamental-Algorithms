#include "HashTable.h"

HashTable::HashTable() {
    int cant_datos, size;
    cout << "¿Cuántos datos tienes?" << endl;
    cin >> cant_datos;
    cout << "¿En cuántos buckets quieres que se almacenen?" << endl;
    cin >> size;
    this->size = size;
#include "HashTable.h"

HashTable::HashTable() {
    int cant_datos, size;
    cout << "¿Cuántos datos tienes?" << endl;
    cin >> cant_datos;
    cout << "¿En cuántos buckets quieres que se almacenen?" << endl;
    cin >> size;
    this->size = size;
    this->cant_datos = cant_datos;
    this->array = new Buckets[this->size];
    int num_buckets, residuo, bucket_key;
    num_buckets = cant_datos / size;
    residuo = cant_datos % size;
    bucket_key = cant_datos / num_buckets;

    if (residuo != 0) {
        if (residuo % num_buckets > 0) {
            int res = residuo / num_buckets;
            bucket_key = bucket_key + res;
        }
    }

    for (int i = 0; i < size; i++) {
        this->array[i].key = bucket_key;
        bucket_key++;
    }
}

int HashTable::hashFunction(int ip) {
    int clave;
    for (int i = 0; i < size; i++) {
        if (ip < array[i].key) {
            clave = array[i].key;
            return clave;
        }
    }
    return 0;
}

void HashTable::insert(int ip) {
    int key = hashFunction(ip);
    for (int i = 0; i < size; i++) {
        if (array[i].key == key) {
            array[i].list.push(ip, ip);
        }
    }
}

void HashTable::remove(int key) {
    for (int i = 0; i < size; i++) {
        if (array[i].key == key) {
            array[i].list.dell();
        }
    }
}

void HashTable::print(int key) {
    for (int i = 0; i < size; i++) {
        if (array[i].key == key) {
            array[i].list.print();
        }
    }
}

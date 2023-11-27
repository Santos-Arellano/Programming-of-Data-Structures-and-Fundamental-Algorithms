#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <iostream>
#include "LinkedList.h"

using namespace std;

struct Buckets {
    int key;
    LinkedList list;
};

class HashTable {
public:
    int size;
    int cant_datos;
    Buckets *array;

    HashTable();
    ~HashTable();
    void insert(int key, int value);
    void remove(int key);
    void print(int key);
};

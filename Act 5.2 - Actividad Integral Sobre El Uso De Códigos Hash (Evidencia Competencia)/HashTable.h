#ifndef HASHTABLE_H
#define HASHTABLE_H

#include "LinkedList.h"
#include <iostream>
using namespace std;

struct Buckets {
    int key;
    LinkedList list;
};

class HashTable {
public:
    int size;
    int cant_datos;
    Buckets* array;

    HashTable();
    int hashFunction(int ip);
    void insert(int ip);
    void remove(int key);
    void print(int key);
};

#endif

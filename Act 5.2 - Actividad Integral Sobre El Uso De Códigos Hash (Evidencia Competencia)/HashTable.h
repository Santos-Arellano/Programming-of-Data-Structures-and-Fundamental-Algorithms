#pragma once
#include <iostream>
#include <string>
#include "LinkedList.h"
using namespace std;

struct Buckets {
    long long key;
    LinkedList list;
};

class HashTable {
public:
    int size;
    int bucketSize;
    Buckets* array;

    HashTable();
    long long hashFunction(long long ip);
    void insert(long long ip, const string& line);
    void print(long long ip);
};


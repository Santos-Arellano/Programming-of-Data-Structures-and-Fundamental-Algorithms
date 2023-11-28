#include "HashTable.h"

HashTable::HashTable() {
    size = 100;
    bucketSize = 1600;
    array = new Buckets[size];
}

long long HashTable::hashFunction(long long ip) {
    return (ip / bucketSize) % size;
}

void HashTable::insert(long long ip, const string& line) {
    long long key = hashFunction(ip);
    array[key].key = key;
    array[key].list.push(ip, line);
}

void HashTable::print(long long ip) {
    long long key = hashFunction(ip);
    array[key].list.print();
}

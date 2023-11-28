#pragma once
#include <iostream>
using namespace std;

struct node {
    long long data;
    string line;
    struct node* next;
};

class LinkedList {
public:
    // Propiedades
    node* head;
    node* tail;

    // Métodos
    LinkedList();
    void push(long long num, const string& line);
    void print();
};


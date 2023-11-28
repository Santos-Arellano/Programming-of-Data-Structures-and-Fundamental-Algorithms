#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <iostream>
using namespace std;

struct node {
    int data;
    int line;
    struct node *next;
};

class LinkedList {
public:
    node *head;
    node *tail;

    LinkedList();
    void push(int, int);
    void dell();
    void print();
};

#endif

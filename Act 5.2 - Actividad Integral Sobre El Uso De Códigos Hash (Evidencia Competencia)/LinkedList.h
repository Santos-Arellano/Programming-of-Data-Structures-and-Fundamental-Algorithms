#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <iostream>
using namespace std;

struct Node {
    int data;
    struct Node *next;
};

class LinkedList {
public:
    // Properties
    Node *head;
    Node *tail;

    // Methods
    LinkedList();
    void push(int);
    void del();
};

#endif

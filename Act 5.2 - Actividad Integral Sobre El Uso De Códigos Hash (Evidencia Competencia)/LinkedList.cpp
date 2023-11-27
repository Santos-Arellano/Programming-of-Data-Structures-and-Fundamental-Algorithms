#include "LinkedList.h"

LinkedList::LinkedList() {
    this->head = nullptr;
    this->tail = nullptr;
}

void LinkedList::push(int num) {
    Node *nodo = new Node;
    nodo->data = num;
    nodo->next = head;
    head = nodo;
}

void LinkedList::del() {
    if (head != nullptr) {
        Node *temp = head;
        head = head->next;
        delete temp;
    }
}

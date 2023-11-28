#include "LinkedList.h"

LinkedList::LinkedList() {
    this->head = NULL;
    this->tail = head;
}

void LinkedList::push(int num, int line) {
    node *nodo = new node;
    nodo->data = num;
    nodo->line = line;
    nodo->next = head;
    head = nodo;
}

void LinkedList::dell() {
    if (head != nullptr) {
        node *temp = head;
        head = head->next;
        delete temp;
    }
}

void LinkedList::print() {
    node *current = head;
    while (current != nullptr) {
        cout << current->data << " ";
        current = current->next;
    }
    cout << endl;
}

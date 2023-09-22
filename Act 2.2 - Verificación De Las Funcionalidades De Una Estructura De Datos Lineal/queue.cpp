#include <iostream>
using namespace std;

class Node {
public:
    int data;
    Node* next;

    Node(int data, Node* next = nullptr) : data(data), next(next) {}
};

class LinkedListQueue {
private:
    Node* head;
    Node* tail;
    int size;
    int capacity;

public:
    LinkedListQueue(int capacity) : head(nullptr), tail(nullptr), size(0), capacity(capacity) {}

    // Comprueba si la cola está llena.
    bool isFull() {
        return size == capacity;
    }

    // Comprueba si la cola está vacía.
    bool isEmpty() {
        return size == 0;
    }

    // Agrega un elemento a la cola con prioridad.
    void enqueue(int data) {
        if (isFull()) {
            cout << "Queue is full" << endl;
            return;
        }

        Node* new_node = new Node(data);

        if (isEmpty()) {
            head = tail = new_node;
        } else if (new_node->data < tail->data) {
            Node* current_node = tail;
            while (current_node->next != nullptr && current_node->next->data > new_node->data) {
                current_node = current_node->next;
            }
            new_node->next = current_node->next;
            current_node->next = new_node;
            if (new_node->next == nullptr) {
                head = new_node;
            }
        } else {
            new_node->next = tail;
            tail = new_node;
        }

        size++;
    }

    // Elimina y devuelve el elemento de mayor prioridad.
    int dequeue() {
        if (isEmpty()) {
            cout << "La lista ligada está vacía" << endl;
            return 0;
        }

        int data = head->data;
        Node* temp = head;

        if (head == tail) {
            head = tail = nullptr;
        } else {
            head = head->next;
        }

        delete temp;
        size--;

        return data;
    }

    // Muestra el contenido de la cola.
    void display() {
        cout << "[";
        Node* current = tail;

        while (current != nullptr) {
            cout << current->data;
            if (current->next != nullptr) {
                cout << " -> ";
            }
            current = current->next;
        }

        cout << "nullptr]" << endl;
    }
};

int main() {
    LinkedListQueue queue(5);
    queue.enqueue(4);
    queue.display();
    queue.enqueue(8);
    queue.display();
    queue.enqueue(2);
    queue.display();
    queue.enqueue(3);
    queue.display();
    queue.enqueue(1);
    queue.display();
    queue.dequeue();
    queue.display();
    queue.dequeue();
    queue.display();
    queue.dequeue();
    queue.display();
    queue.dequeue();
    queue.display();
    queue.dequeue();
    queue.display();
    queue.dequeue();
    return 0;
}

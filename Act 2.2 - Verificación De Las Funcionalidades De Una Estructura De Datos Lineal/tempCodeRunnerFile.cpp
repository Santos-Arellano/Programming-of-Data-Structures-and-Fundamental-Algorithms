#include <iostream>
using namespace std;

class Node{
    public:
        int data;
        Node* next;
        Node(int data, Node* next);
};

Node::Node(int data, Node* next){
    this->data = data;
    this->next = next;
}

class Linkedlist_queue{
    public: 
        Node* head;
        Node* tail;
        int size;
        int capacity;
        Linkedlist_queue();
        void enqueue(int);
        int dequeue();
        bool isEmpty();
        bool isFull();
        void display();
};

Linkedlist_queue::Linkedlist_queue(){
    this->head = nullptr;
    this->tail = nullptr;
    size = 0;
    capacity = 5;
}

void Linkedlist_queue::enqueue(int data){
    if(isFull()){
        cout << "Queue is full" << endl;
    }else{
        Node* new_node = new Node(data, nullptr);
        if(this->head== nullptr && this->tail==nullptr){
            new_node->next = this->head;
            this->head = new_node;
            this->tail = new_node;
            size += 1;
        }else if(new_node->data < this->tail->data){
            Node* current_node = this->tail;
            while(current_node->next != nullptr && current_node->next->data > new_node->data){
                current_node = current_node->next;
            }
            new_node->next = current_node->next;
            current_node->next = new_node;
            size += 1;
            if(new_node->next == nullptr){
                this->head = new_node;
            }
        }else{
            new_node->next = this->tail;
            this->tail = new_node;
            size += 1;
        }
    }
}

int Linkedlist_queue::dequeue(){
    if(isEmpty()){
        cout << "La lista ligada está vacia" << endl;
        return 0;
    }else if(this->head->next == nullptr && this->tail->next == nullptr){
        Node* head_tail_ptr = this->head;
        int head_tail_data = this->head->data;
        this->head = nullptr;
        this->tail = nullptr;
        delete head_tail_ptr;
        return head_tail_data;
    }else{
        Node* tail_anterior = this->tail;
        int tail_anterior_data = this->tail->data;
        this->tail = this->tail->next;
        delete tail_anterior;
        return tail_anterior_data;
    }
}

void Linkedlist_queue::display(){
    Node* current_tail = this->tail;
    cout<<"[";
    while(current_tail != nullptr){
        cout<<current_tail->data<<"->";
        current_tail = current_tail->next;
    }
    cout<<"nullptr"<<"]"<<endl;
}

bool Linkedlist_queue::isEmpty(){
    if(this->head== nullptr && this->tail==nullptr){
        return true;
    }
    return false;
}

bool Linkedlist_queue::isFull(){
    if(capacity==size){
        return true;
    }
    return false;
}


int main(){
    Linkedlist_queue queue;
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
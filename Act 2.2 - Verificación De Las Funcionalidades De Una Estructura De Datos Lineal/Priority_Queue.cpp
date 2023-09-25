#include <iostream>
using namespace std;

struct node
{
    int data;
    struct node *next;
};

class LinkedList
{
public:
    // Propiedades
    node *head;
    node *tail;

    // Métodos
    LinkedList();
    void push(int);
    void dell();
};

LinkedList::LinkedList()
{
    this->head = nullptr;
    this->tail = nullptr;
}

void LinkedList::push(int num){
    node *nodo = new node; 
    nodo->data = num;
    nodo->next = head;
    head = nodo;
}

void LinkedList::dell()
{
    if (head != nullptr)
    {
        node *temp = head;
        head = head->next;
        delete temp;
    }
}

class Priority_Queue
{
private:
    LinkedList Lista;
    int max;

public:
    Priority_Queue();
    void Push(int num);
    int Pop();
    bool isEmpty();
};

Priority_Queue::Priority_Queue()
{
    this->max = 0;
}

void Priority_Queue::Push(int num)
{
        if (num >= this->max)
        {
            Lista.push(num);
            this->max = num;
        }
        else
        {
            node *actual=Lista.head;
            node *anterior=nullptr;
            while(actual&&num<actual->data){
                anterior=actual;
                actual=actual->next;
            }
            node *nuevo_nodo= new node;
            nuevo_nodo->data=num;
            nuevo_nodo->next=actual;
            if(anterior!=nullptr){
                anterior->next=nuevo_nodo;
            }else{
                Lista.head=nuevo_nodo;
            }
        }
}

int Priority_Queue::Pop()
{
    if (!isEmpty())
    {
        int temp = max;
        Lista.dell();
        if (Lista.head)
        {
            max = Lista.head->data;
        }
        else
        {
            max = 0;
        }
        return temp;
    }
    else
    {
        cout << "La cola de prioridad está vacía." << endl;
        return -1; 
    }
}

bool Priority_Queue::isEmpty()
{
    return Lista.head == nullptr;
}

int main()
{
    Priority_Queue pq;
    pq.Push(10);
    pq.Push(8);
    pq.Push(11);
    pq.Push(12);
    pq.Push(2);
    pq.Push(3);
    pq.Push(4);
    pq.Push(5);
    pq.Push(5);
    pq.Push(0);
    pq.Push(-10);

    while (!pq.isEmpty())
    {
        cout << pq.Pop() << " ";
    }
    cout << endl;

    return 0;
}

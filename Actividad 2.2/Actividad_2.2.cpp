#include <iostream>
using namespace std;

struct node
{
 int data;
 struct node *next;
};
class LinkedList{
    public:
    //Properties
    node *head;
    node *tail;
    //Methods
    LinkedList();
    void push(int);
    void dell();
};
LinkedList::LinkedList(){
    this->head = NULL;
    this->tail=head;
}
void LinkedList::push(int num){
    node *nodo = new node; 
    nodo->data = num;
    nodo->next = head;
    head = nodo;
}
void LinkedList::dell(){
    if (head != nullptr)
    {
        node *temp=head;
        head=head->next;
        delete temp;
    }
}
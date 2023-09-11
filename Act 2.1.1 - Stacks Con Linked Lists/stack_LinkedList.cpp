#include <iostream>
using namespace std;
#define SIZE 10
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

class Stack {
    //Properties
    LinkedList list;
    int top;
    int capacity;
    //Methods
    public:
        Stack();
        void push(int);
        int pop();
        int peak();
        int size();
        bool isEmpty();
};
//Definition of methods
Stack::Stack(){
    this->capacity=0;
    this->top=-1;
}
void Stack::push(int num ){
    this->top=num;
    list.push(num);
    capacity++;
}
int Stack::pop(){
    if(isEmpty()){
        cout<<"El arreglo estsa vacio actualmente y no se pueden eliminar elementos"<<endl;
        return 0;
    }else{
        int num=top;
        list.dell();
        if (list.head != nullptr)
        {
            top=list.head->data;
        }else{
            top=-1;
        }
        capacity--;
        return num;
    }
}
int Stack::peak(){
    if(isEmpty()){
        cout<<"El arreglo esta vacio actualmente por lo que no se puede encontrar el peak"<<endl;
        return -1;
    }else{
        return top;
    }
}
int Stack::size(){
    return capacity;
}
bool Stack::isEmpty(){
    return (top==0&&capacity==0);
}

int main(){
    Stack stak;
    cout<<"Vacio "<<stak.isEmpty()<<endl;
    stak.push(10);
    stak.push(20);
    stak.push(30);
    stak.push(40);
    stak.push(50);
    stak.push(60);
    stak.push(70);
    stak.push(80);
    stak.push(90);
    stak.push(100);
    stak.push(110);

    cout<<stak.pop()<<endl;
    cout<<stak.pop()<<endl;
    cout<<stak.pop()<<endl;

    cout<<"Peak: "<<stak.peak()<<endl;
    cout<<"Size: "<<stak.size()<<endl;
    
   
    return 0;
}
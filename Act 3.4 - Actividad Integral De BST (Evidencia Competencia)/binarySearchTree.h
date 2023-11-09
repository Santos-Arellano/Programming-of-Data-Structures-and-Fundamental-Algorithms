#include <iostream>
using namespace std;
struct node{
    public:
        int data;
        int puerto;
        node* right;
        node* left;
        node(){
            data = 1;
            right = nullptr;
            left = nullptr;
        }
};

class BinarySearchTree{
public:
   node *raiz;
   int altura;
   node* puertos[5];
   BinarySearchTree();
   void push(int num);
   void preOrder(node* root);
   void inOrder(node* root);
   void postOrder(node* root);
   void levelByLevel(node* root,int num);
   void visit(BinarySearchTree* arbolito);
   int height(node* root);
};
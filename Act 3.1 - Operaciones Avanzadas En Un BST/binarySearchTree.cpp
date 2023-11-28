#include <iostream>
using namespace std;
struct node{
    public:
        int data;
        node* right;
        node* left;
        node(){
            data = 0;
            right = nullptr;
            left = nullptr;
        }
};


class BinarySearchTree{
private:
   node *raiz;
   int altura;
public:
   BinarySearchTree();
   void push(int num);
   void preOrder(node* root);
   void inOrder(node* root);
   void postOrder(node* root);
   void levelByLevel(node* root,int num);
   void visit(BinarySearchTree* arbolito);
   int height(node* root);
   int whatLevelIAm(int num);
   int ancestors(int num);
};
BinarySearchTree::BinarySearchTree(){
    altura=0;
    raiz=nullptr;
}


void BinarySearchTree::push(int num){
    node* nodo=new node;
    nodo->data=num;
    if(raiz==nullptr){
        raiz=nodo;
        altura+=1;
    }else{
        node*ptr=raiz;
        while(ptr!=nullptr){
           if(nodo->data<ptr->data&&ptr->left==nullptr){
                ptr->left=nodo;
                break;
            }else if(nodo->data>ptr->data&&ptr->right==nullptr){
                ptr->right=nodo;
                break;
            }else if(nodo->data==ptr->data){
                cout<<"Ese valor ya habia sido ingresado, intenta con otro"<<endl;
                return;
            }else if(nodo->data<ptr->data){
                ptr=ptr->left;
            }else{
                ptr=ptr->right;
               
            }
        }
    }
}
void BinarySearchTree::preOrder(node* root){
    if(root==nullptr){
        return;
    }
    cout<<root->data<<" ";
    preOrder(root->left);
    preOrder(root->right);
}
void BinarySearchTree::inOrder(node* root){
    if (root == nullptr){
        return;
    }
    inOrder(root->left);
    cout << root->data << " ";
    inOrder(root->right);
}
void BinarySearchTree::postOrder(node* root){
    if (root == nullptr){
        return;
    }
    postOrder(root->left);
    postOrder(root->right);
    cout << root->data << " ";
}
void BinarySearchTree::levelByLevel(node* root, int level) {
    if (root == nullptr) {
        return;
    }


    if (level == 1) {
        cout << root->data << " ";
    }
    else if (level > 1) {
        levelByLevel(root->left, level - 1);
        levelByLevel(root->right, level - 1);
    }
}
void BinarySearchTree::visit(BinarySearchTree* arbolito){
    int op=0;
    cout<<"Introduce un numero entero del 1 al 4 para decir como quieres que muestre el BinarySearchTree"<<endl;
    cout<<"1. preOrder"<<endl;
    cout<<"2. inOrder"<<endl;
    cout<<"3. postOrder"<<endl;
    cout<<"4. Level by level"<<endl;
    cin>>op;
    if(op==1){
        cout<<"Opcion seleccionada (1. preOrder)"<<endl;
        arbolito->preOrder
(arbolito->raiz);
        cout<<endl;
   
    }else if(op==2){
        cout<<"Opcion seleccionada (2. inOrder)"<<endl;
        arbolito->inOrder(arbolito->raiz);
        cout<<endl;
   
    }else if(op==3){
        cout<<"Opcion seleccionada (3. postOrder)"<<endl;
        arbolito->postOrder
(arbolito->raiz);
        cout<<endl;
    }else if(op==4){
        cout<<"Opcion seleccionada (4. Level by level)"<<endl;
        for (int i = 1; i <= arbolito->height(arbolito->raiz); i++) {
            cout << "Nivel " << i << ": ";
            arbolito->levelByLevel(arbolito->raiz, i);
            cout << endl;
        }
    }else{
        cout<<"Esa no es una opcion disponible"<<endl;
    }
}


int BinarySearchTree::height(node* root) {
    if (root == nullptr) {
        return 0;
    } else {
        int leftHeight = height(root->left);
        int rightHeight = height(root->right);
        if(leftHeight>=rightHeight){
            altura=leftHeight+1;
        }else{
            altura=rightHeight+1;
        }
        return altura;
    }
}
int BinarySearchTree::whatLevelIAm(int num){
    int cont=0;
    node* nodo=new node;
    nodo->data=num;
    node*ptr=raiz;
    while(ptr!=nullptr){
        if(ptr->data>num&&ptr->left!=nullptr){
            ptr=ptr->left;
            cont+=1;
        }else if(ptr->data<num&&ptr->right!=nullptr){
            ptr=ptr->right;
            cont+=1;
        }else if(ptr->data==num){
            cont+=1;
            return cont;
        }  
    }
    if(cont>0){
        return cont;
    }else{
        return -1;
    }
}
int BinarySearchTree::ancestors(int num){
    int cont=0;
    node* nodo=new node;
    nodo->data=num;
    node*ptr=raiz;
    while(ptr!=nullptr){
        if(ptr->data>num&&ptr->left!=nullptr){
            cont+=1;
            cout<<"Ancestro "<<cont<<": "<<ptr->data<<endl;
            ptr=ptr->left;
        }else if(ptr->data<num&&ptr->right!=nullptr){
            cont+=1;
            cout<<"Ancestro "<<cont<<": "<<ptr->data<<endl;
            ptr=ptr->right;
        }else if(ptr->data==num){
            cont+=1;
            cout<<"Descendiente: "<<ptr->data<<endl;
            return cont;
        }  
    }
    if(cont>0){
        return cont;
    }else{
        return -1;
    }
}
int main(){
    BinarySearchTree arbolito;
    arbolito.push(7);
    arbolito.push(9);
    arbolito.push(8);
    arbolito.push(7);
    arbolito.push(2);
    arbolito.push(3);
    arbolito.push(4);
    arbolito.push(1);
    arbolito.push(5);
    arbolito.push(12);
    arbolito.visit(&arbolito);
    cout<<endl;
    cout<<"Nivel en el cual se encuentra el 4 en el BinarySearchTree: "<<arbolito.whatLevelIAm(4)<<endl;
    cout<<endl;
    arbolito.ancestors(8);
    cout<<endl;
}

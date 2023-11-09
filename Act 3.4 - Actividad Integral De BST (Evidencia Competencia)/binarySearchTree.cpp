/**
 * @brief This code snippet defines a C++ class called BinarySearchTree. 
 *        It implements various methods for manipulating a binary search tree, such as inserting nodes, traversing the tree in different orders, and displaying the tree level by level.
 * 
 * @details The class has the following methods:
 *          - push(int num): Inserts a node with the given value into the binary search tree.
 *          - preOrder(node* root): Traverses the tree in pre-order and prints the node values.
 *          - inOrder(node* root): Traverses the tree in in-order and prints the node values.
 *          - postOrder(node* root): Traverses the tree in post-order and prints the node values.
 *          - levelByLevel(node* root, int num): Prints the nodes at a given level of the tree.
 *          - visit(BinarySearchTree* arbolito): Prompts the user to select a traversal method and prints the tree accordingly.
 *          - height(node* root): Calculates and returns the height of the tree.
 * 
 * @note The BinarySearchTree class uses a struct called node to represent each node in the tree. Each node contains an integer value, a port number, and pointers to its left and right children.
 *       The class also maintains an array of node pointers called puertos, which is used to keep track of the nodes with the highest data values.
 * 
 * @example Usage:
 *          BinarySearchTree bst;
 *          bst.push(5);
 *          bst.push(3);
 *          bst.push(7);
 *          bst.visit(&bst);
 * 
 *          Expected Output:
 *          Introduce un numero entero del 1 al 4 para decir como quieres que muestre el BST
 *          1. Preorder
 *          2. Inorder
 *          3. Postorder
 *          4. Level by level
 */
// binarySearchTree.cpp

#include <iostream>
using namespace std;

struct node {
    int data;
    int puerto;
    node* right;
    node* left;
    node() {
        data = 1;
        right = nullptr;
        left = nullptr;
    }
};

class BinarySearchTree {
public:
    node *raiz;
    int altura;
    node* puertos[5];
    BinarySearchTree();
    void push(int num);
    void preOrder(node* root);
    void inOrder(node* root);
    void postOrder(node* root);
    void levelByLevel(node* root, int num);
    void visit(BinarySearchTree* arbolito);
    int height(node* root);
};

BinarySearchTree::BinarySearchTree() {
    altura = 0;
    raiz = nullptr;
    for (int i = 0; i < 5; i++) {
        puertos[i] = nullptr;
    }
}

void BinarySearchTree::push(int num) {
    node* nodo = new node;
    nodo->puerto = num;

    for (int i = 0; i < 5; i++) {
        if (puertos[i] != nullptr && puertos[i]->puerto == num) {
            puertos[i]->data++;
            return;
        }
    }

    if (raiz == nullptr) {
        raiz = nodo;
        altura += 1;
        puertos[0] = nodo;
    } else {
        node* ptr = raiz;
        while (ptr != nullptr) {
            if (nodo->puerto < ptr->puerto && ptr->left == nullptr) {
                ptr->left = nodo;
                break;
            } else if (nodo->puerto > ptr->puerto && ptr->right == nullptr) {
                ptr->right = nodo;
                break;
            } else if (nodo->puerto == ptr->puerto) {
                ptr->data++;
                for (int i = 0; i < 5; i++) {
                    if (puertos[i] == nullptr || ptr->data > puertos[i]->data) {
                        for (int j = 4; j > i; j--) {
                            puertos[j] = puertos[j - 1];
                        }
                        puertos[i] = ptr;
                        break;
                    }
                }
                return;
            } else if (nodo->puerto < ptr->puerto) {
                ptr = ptr->left;
            } else {
                ptr = ptr->right;
            }
        }
    }
}

void BinarySearchTree::preOrder(node* root) {
    if (root == nullptr) {
        return;
    }
    cout << root->data << " ";
    cout << root->puerto << " ";
    preOrder(root->left);
    preOrder(root->right);
}

void BinarySearchTree::inOrder(node* root) {
    if (root == nullptr) {
        return;
    }
    inOrder(root->left);
    cout << root->data << " ";
    inOrder(root->right);
}

void BinarySearchTree::postOrder(node* root) {
    if (root == nullptr) {
        return;
    }
    postOrder(root->left);
    postOrder(root->right);
    cout << root->data << " ";
}

void BinarySearchTree::levelByLevel(node* root, int num) {
    if (root == nullptr) {
        return;
    }

    if (num == 1) {
        cout << root->puerto << " ";
    } else if (num > 1) {
        levelByLevel(root->left, num - 1);
        levelByLevel(root->right, num - 1);
    }
}

void BinarySearchTree::visit(BinarySearchTree* arbolito) {
    int op = 0;
    cout << "Introduce un numero entero del 1 al 4 para decir como quieres que muestre el BST" << endl;
    cout << "1. Preorder" << endl;
    cout << "2. Inorder" << endl;
    cout << "3. Postorder" << endl;
    cout << "4. Level by level" << endl;
    cin >> op;
    if (op == 1) {
        cout << "Opcion seleccionada (1. Preorder)" << endl;
        arbolito->preOrder(arbolito->raiz);
        cout << endl;
    } else if (op == 2) {
        cout << "Opcion seleccionada (2. Inorder)" << endl;
        arbolito->inOrder(arbolito->raiz);
        cout << endl;
    } else if (op == 3) {
        cout << "Opcion seleccionada (3. Postorder)" << endl;
        arbolito->postOrder(arbolito->raiz);
        cout << endl;
    } else if (op == 4) {
        cout << "Opcion seleccionada (4. Level by level)" << endl;
        int height = arbolito->height(arbolito->raiz);
        for (int i = 1; i <= height; i++) {
            cout << "Nivel " << i << ": ";
            arbolito->levelByLevel(arbolito->raiz, i);
            cout << endl;
        }
    } else {
        cout << "Esa no es una opcion disponible" << endl;
    }
}

int BinarySearchTree::height(node* root) {
    if (root == nullptr) {
        return 0;
    } else {
        int leftHeight = height(root->left);
        int rightHeight = height(root->right);
        altura = max(leftHeight, rightHeight) + 1;
        return altura;
    }
}

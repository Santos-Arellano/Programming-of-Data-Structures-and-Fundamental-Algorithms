#include <iostream>
#include <list>
#include <stack>
#include <queue>
#include <vector>
#include <algorithm>
using namespace std;

class Graph {
private:
    int V; // número de vértices
    int E; // número de arcos
    list<int> *adj; // Lista de adyacencia
public:
    Graph(int V, int E);
    void addEdge(int v, int w);
    void DFS(int s);
    void BFS(int s);
    void loadGraph();
    bool isTree();
    void topologicalSort();
    void topologicalSortUtil(int v, bool visited[], stack<int> &resultStack);
    bool bipartiteGraph();
    void displayList();
};

Graph::Graph(int V, int E) {
    this->V = V;
    this->E = E;
    adj = new list<int>[V];
    loadGraph();
}

void Graph::addEdge(int v, int w) {
    adj[v].push_back(w);
}

void Graph::loadGraph() {
    int num1, num2;
    for (int i = 0; i < E; i++) {
        cout << "Ingresa el nodo al que le quieres añadir una conexión" << endl;
        cin >> num1;
        cout << "Ingresa el nodo con el que lo quieres conectar" << endl;
        cin >> num2;
        addEdge(num1, num2);
    }
}

void Graph::DFS(int s) {
    bool *visited = new bool[V];
    for (int i = 0; i < V; i++) {
        visited[i] = false;
    }
    stack<int> stack;
    stack.push(s);
    while (!stack.empty()) {
        s = stack.top();
        stack.pop();
        if (!visited[s]) {
            cout << s << " ";
            visited[s] = true;
        }
        for (list<int>::iterator i = adj[s].begin(); i != adj[s].end(); ++i) {
            if (!visited[*i]) {
                stack.push(*i);
            }
        }
    }
}

void Graph::BFS(int s) {
    bool *visited = new bool[V];
    for (int i = 0; i < V; i++) {
        visited[i] = false;
    }
    queue<int> queue;
    queue.push(s);
    while (!queue.empty()) {
        s = queue.front();
        queue.pop();
        if (!visited[s]) {
            cout << s << " ";
            visited[s] = true;
        }
        for (list<int>::iterator i = adj[s].begin(); i != adj[s].end(); ++i) {
            if (!visited[*i]) {
                queue.push(*i);
            }
        }
    }
}

void Graph::displayList() {
    cout << "--------------------------------" << endl;
    cout << "Lista de adyacencia" << endl;
    for (int i = 0; i < V; i++) {
        cout << "vertice: " << i << " [";
        for (list<int>::iterator j = adj[i].begin(); j != adj[i].end(); j++) {
            cout << *j << " ";
        }
        cout << "]" << endl;
    }
    cout << "--------------------------------" << endl;
}

bool Graph::isTree() {
    int s = 0;
    bool *visited = new bool[V];
    if (E >= V) {
        return false;
    }
    for (int i = 0; i < V; i++) {
        visited[i] = false;
    }
    stack<int> stack;
    stack.push(s);

    while (!stack.empty()) {
        s = stack.top();
        stack.pop();
        if (!visited[s]) {
            visited[s] = true;
        } else {
            return false;
        }
        for (list<int>::iterator i = adj[s].begin(); i != adj[s].end(); ++i) {
            if (!visited[*i]) {
                stack.push(*i);
            }
        }
    }
    for (int n = 0; n < V; n++) {
        if (visited[n] == false) {
            return false;
        }
    }
    return true;
}

bool Graph::bipartiteGraph() {
    int s = 0;
    bool *visited = new bool[V];
    bool *colors = new bool[V];
    for (int i = 0; i < V; i++) {
        visited[i] = false;
        if (i % 2 == 0) {
            colors[i] = false;
        } else if (i == 0) {
            colors[i] = false;
        } else {
            colors[i] = true;
        }
    }
    queue<int> queue;
    queue.push(s);
    while (!queue.empty()) {
        s = queue.front();
        queue.pop();
        if (!visited[s]) {
            visited[s] = true;
        }
        for (list<int>::iterator i = adj[s].begin(); i != adj[s].end(); ++i) {
            if (!visited[*i]) {
                queue.push(*i);
                if (colors[s] == colors[*i]) {
                    cout << "No es bipartito." << endl;
                    return false;
                }
            }
        }
    }
    cout << "Es bipartito." << endl;
    return true;
}

void Graph::topologicalSort() {
    stack<int> resultStack;
    bool *visited = new bool[V];
    for (int i = 0; i < V; i++) {
        visited[i] = false;
    }
    for (int i = 0; i < V; i++) {
        if (!visited[i]) {
            topologicalSortUtil(i, visited, resultStack);
        }
    }
    cout << "Orden topológico: ";
    while (!resultStack.empty()) {
        cout << resultStack.top() << " ";
        resultStack.pop();
    }
    cout << endl;
}

void Graph::topologicalSortUtil(int v, bool visited[], stack<int> &resultStack) {
    visited[v] = true;
    for (list<int>::iterator i = adj[v].begin(); i != adj[v].end(); ++i) {
        if (!visited[*i]) {
            topologicalSortUtil(*i, visited, resultStack);
        }
    }
    resultStack.push(v);
}

int main() {
    int V, E;
    cout << "Dime el numero de vertices para tu grafo" << endl;
    cin >> V;
    cout << "Dime el numero de conexiones en tu grafo" << endl;
    cin >> E;
    Graph g(V, E);
    g.displayList();
    
    // Evaluar si es un árbol
    if (g.isTree()) {
        cout << "Es un árbol." << endl;
    } else {
        cout << "No es un árbol." << endl;
    }

    // Evaluar si es bipartito
    if (g.bipartiteGraph()) {
        cout << "Es bipartito." << endl;
    } else {
        cout << "No es bipartito." << endl;
    }

    // Orden topológico
    g.topologicalSort();

    return 0;
}

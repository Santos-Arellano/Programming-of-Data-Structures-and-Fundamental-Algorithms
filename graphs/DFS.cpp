#include <iostream>
#include <list>
#include <stack>

using namespace std;

class Graph {
    private:
        int V; // Número de vértices
        list<int> *adj; // Lista de adyacencia que apunta a un array de listas

    public:
        Graph(int V); // Constructor
        void addEdge(int v, int w); // Función para agregar una arista al grafo
        void DFS(int s); // Recorrido DFS a partir de un vértice s
        void DFSUtil(int v, bool visited[]); // Función de utilidad para el recorrido DFS
}; 

Graph::Graph(int V) { // Constructor
    this->V = V;
    adj = new list<int>[V];
}

void Graph::addEdge(int v, int w) { // Función para agregar una arista al grafo
    adj[v].push_back(w);
}

void Graph::DFSUtil(int v, bool visited[]) { // Recorrido DFS a partir de un vértice s
    visited[v] = true; // Marcar el vértice actual como visitado y mostrarlo
    cout << v << " "; // Recorrer todos los vértices adyacentes al vértice actual

    list<int>::iterator i; // Recorrer todos los vértices adyacentes al vértice actual
    for (i = adj[v].begin(); i != adj[v].end(); ++i) { // Si un vértice adyacente no ha sido visitado, llamar recursivamente a la función DFSUtil para ese vértice
        if (!visited[*i]) 
            DFSUtil(*i, visited);
        }
    }


void Graph::DFS(int s) {
    bool *visited = new bool[V];
    for (int i = 0; i < V; i++) {
        visited[i] = false;
    }

    DFSUtil(s, visited);
}

int main() {
    Graph g(4);
    g.addEdge(0, 1);
    g.addEdge(0, 2);
    g.addEdge(1, 2);
    g.addEdge(2, 0);
    g.addEdge(2, 3);
    g.addEdge(3, 3);

    cout << "DFS(2): ";
    g.DFS(2);
    cout << endl;

    return 0;
}

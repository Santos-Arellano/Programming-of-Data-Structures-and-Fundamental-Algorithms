#include <iostream>
#include <list>
#include <stack>

using namespace std;

class Graph {
    private:
        int V; //number of vertices
        list<int> *adj; //adj list que apunta a un array de listas

    public:
        Graph(int V); //constructor
        void addEdge(int v, int w); //funcion para agregar una arista al grafo donde 
        void DFS(int s); //recorrido DFS a partir de un vertice s dond s significa "source"
}; 

Graph::Graph(int V){ //constructor
    this ->V = V; //inicializa el numero de vertices
    adj = new list<int>[V]; //crea un array de listas de tamaño V

}

void Graph::addEdge(int v, int w){ 
    adj[v].push_back(w); //agrega w a la lista de v donde w son vertices
    //adj [w].push_back(v); //agrega v a la lista de w donde v son vertices
}

void Graph::DFS(int s){
    bool *visited = new bool[V]; //crea un array de booleanos de tamaño V

    for (int i= 0; i < V; i++){
        visited[i] = false; //inicializa todos los vertices como no visitados
    }

stack<int> stack; //crea una pila de tipo stack
stack .push(s); //inserta el vertice de origen a la pila

while(!stack.empty()) {
    s = stack.top(); //saca un vertice de la pila
    stack.pop(); //elimina el vertice de la pila

    if (!visited[s]){
        cout << s << " "; //imprime el vertice
        visited[s] = true; //marca el vertice como visitado      
    }
    
    for(list<int>::iterator i = adj[s].begin(); i != adj[s].end(); ++i){ //recorre todos los vertices adyacentes de s 
        if (!visited[*i]){ //si no ha sido visitado 
            stack.push(*i); //inserta el vertice adyacente de s si no ha sido visitado
        }
    }
}

}

int main(){
    Graph g(5); //crea un grafo con 5 vertices
    g.addEdge(0,1); //agrega las aristas
    g.addEdge(0,2);
    g.addEdge(1,0);
    g.addEdge(2,0);
    g.addEdge(1,2);
    g.addEdge(1,4);
    g.addEdge(2,1);
    g.addEdge(2,3);
    g.addEdge(3,2);
    g.addEdge(3,4);
    g.addEdge(4,1);

    
    g.DFS(0); //recorrido DFS a partir del vertice 0
    }
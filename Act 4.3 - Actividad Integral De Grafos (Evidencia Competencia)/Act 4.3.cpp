#include <iostream>
#include <list>
#include <sstream>
#include <fstream>
#include <stack>
#include <queue>
#include <set>
using namespace std;
class Graph {
private:
    int V; // número de vértices
    int E; // número de Edges
    set<int> *adj; 
public:
    Graph(int V, int E);
    void addEdge(int v, int w);
    int fanOut(int v);
    void displayList();
    void maxFanOut(int n);
};

Graph::Graph(int V, int E) {
    this->V = V;
    this->E = E;
    adj = new set<int>[V];
}

void Graph::addEdge(int v, int w) {
        adj[v].insert(w);
 
}

int Graph::fanOut(int v) {
        return adj[v].size();
}

void Graph::displayList() {
    cout << "--------------------------------" << endl;
    cout << "Lista de adyacencia" << endl;
    for (int i = 0; i < V; i++) {
        cout << "vertice: " << i << " [";
        for (set<int>::iterator j = adj[i].begin(); j != adj[i].end(); j++) {
            cout << *j << " ";
        }
        cout << "]" << endl;
    }
    cout << "--------------------------------" << endl;
}

void Graph::maxFanOut(int n) {
    int *maxFanOut = new int[n];
    for (int i = 0; i < n; i++) {
        maxFanOut[i] = 0; 
    }
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < n; j++) {
            if ( fanOut(i) > fanOut(maxFanOut[j])) {
                for (int k = n - 1; k > j; k--) {
                    maxFanOut[k] = maxFanOut[k - 1];
                }
                maxFanOut[j] = i;
                break; 
            }
        }
    }
    for (int i = 0; i < n; i++) {
        cout << "Mayor Fan Out numero " << i + 1 << " : " << maxFanOut[i] << " FanOut: " << fanOut(maxFanOut[i]) << endl;
    }
}

string extractIp(std::string line) {
    string mes, dia, hora, ip;
    stringstream extract(line);
    extract >> mes >> dia >> hora >> ip;
    return ip;
}

int main() {
    fstream bitacora("bitacora.txt");
    string line, ip, puerto;
    Graph grafo(1000, 1000);
    int arr[16807][4];
    int cont=0;
    while (getline(bitacora, line)) {
        ip = extractIp(line);
        istringstream iss(ip);
        char dot;
        int parte1, parte2, parte3, parte4;
        iss >> parte1 >> dot >> parte2 >> dot >> parte3 >> dot >> parte4;
        arr[cont][0] = parte1;
        arr[cont][1] = parte2;
        arr[cont][2] = parte3;
        arr[cont][3] = parte4;
        grafo.addEdge(parte1, parte2);
        grafo.addEdge(parte2, parte3);
        grafo.addEdge(parte3, parte4);
        cont=cont +1;
    }
    int fanOut=0;
    int fanOutTemp=0;
    string ipBootMaster="";
    string tempIp="";
    for(int i=0;i<cont;i++){
        for (int j=0;j<4;j++){
            fanOutTemp=fanOutTemp+grafo.fanOut(arr[i][j]);
            if(j<=3){
                tempIp=tempIp+to_string(arr[i][j])+".";
            }else{
                tempIp=tempIp+to_string(arr[i][j]);
            }
        }
        if (fanOutTemp>fanOut){
            fanOut=fanOutTemp;
            ipBootMaster=tempIp;
        }
        fanOutTemp=0;
        tempIp="";
    }
    int n;
    cout<<"Dime el numero de segmentos con mayor Fan Out que quieres conocer "<<endl;
    cin>>n;
    grafo.maxFanOut(n);
    cout<<"Ip BootMaster : "<<ipBootMaster<<" con "<< fanOut<<" conexiones de salida"<<endl;
    return 0;
}

//g++ "Act 4.3.cpp" -o "Act 4.3" -std=c++11

//./"Act 4.3"
#include <iostream>
#include <vector>
#include <queue>

using namespace std;

// Función para cargar los arcos del grafo en una matriz de adyacencia y una lista de adyacencia
void cargarGrafo(int N, int M, vector<vector<int > >& matrizAdj, vector<vector<int > >& listaAdj) {
    matrizAdj.resize(N, vector<int>(N, 0));

    cout << "Ingrese las aristas (u v):" << endl;
    for (int i = 0; i < M; ++i) {
        int u, v;
        cout << "Arista " << i + 1 << " (u v): ";
        cin >> u >> v;

        try {
            // Verifica si los nodos están en el rango correcto
            if (u < 0 || u >= N || v < 0 || v >= N) {
                throw out_of_range("Nodos fuera de rango. Ingrese nodos en el rango de 0 a " + to_string(N - 1) + ".");
            }

            matrizAdj[u][v] = 1;
            matrizAdj[v][u] = 1;

            listaAdj[u].push_back(v);
            listaAdj[v].push_back(u);
        } catch (const out_of_range& e) {
            cout << e.what() << endl;
            cout << "Intenta de nuevo." << endl;
            --i;  // Reintenta la entrada para esta arista
        }
    }
}

// Función para recorrer el grafo utilizando DFS (Profundidad)
void DFSUtil(vector<vector<int > >& matrizAdj, int nodo, vector<bool>& visitado) {
    visitado[nodo] = true;
    cout << nodo << " ";

    for (int i = 0; i < matrizAdj[nodo].size(); ++i) {
        if (matrizAdj[nodo][i] == 1 && !visitado[i]) {
            DFSUtil(matrizAdj, i, visitado);
        }
    }
}

void DFS(vector<vector<int > >& matrizAdj, int nodoInicial) {
    int N = matrizAdj.size();
    vector<bool> visitado(N, false);

    cout << "Recorrido DFS empezando desde el nodo " << nodoInicial << ": ";

    DFSUtil(matrizAdj, nodoInicial, visitado);

    cout << endl;
}

// Función para recorrer el grafo utilizando BFS (Anchura)
void BFS(vector<vector<int > >& listaAdj, int nodoInicial) {
    int N = listaAdj.size();
    vector<bool> visitado(N, false);

    cout << "Recorrido BFS empezando desde el nodo " << nodoInicial << ": ";

    queue<int> q;
    q.push(nodoInicial);
    visitado[nodoInicial] = true;

    while (!q.empty()) {
        int nodo = q.front();
        q.pop();
        cout << nodo << " ";

        for (int i = 0; i < listaAdj[nodo].size(); ++i) {
            int vecino = listaAdj[nodo][i];
            if (!visitado[vecino]) {
                q.push(vecino);
                visitado[vecino] = true;
            }
        }
    }

    cout << endl;
}

int main() {
    int N, M;
    cout << "Ingrese el número de vértices (N): ";
    cin >> N;

    // Validación adicional para evitar divisiones por cero
    while (N <= 0) {
        cout << "Ingrese un número de vértices válido (mayor que cero): ";
        cin >> N;
    }

    cout << "Ingrese el número de aristas (M): ";
    cin >> M;

    vector<vector<int > > matrizAdj(N, vector<int>(N, 0));
    vector<vector<int > > listaAdj(N);

    cargarGrafo(N, M, matrizAdj, listaAdj);

    int nodoInicial;
    cout << "Ingrese el nodo inicial para DFS y BFS: ";
    cin >> nodoInicial;

    DFS(matrizAdj, nodoInicial);
    BFS(listaAdj, nodoInicial);

    return 0;
}

#include <iostream>
#include <vector>
#include <fstream>
#include <queue>
#include <climits>   // profe porsia este lo use lo para poner el INT_MAX
#include <algorithm> // este lo use para el reverse, no encontre otra forma que no fuera o usando cola de prioridad o reverse

/* --------------------------------------------------------------------

    Julian Andre Honores Henriquez - 21.328.088-0 - Estructuras de datos verano 2025

-------------------------------------------------------------------- */

using namespace std;

class Graph
{

public:
    vector<vector<int>> adjacency_matrix;
    int num_nodes;
    vector<int> costs;
    vector<int> visited;
    vector<int> path;

    Graph()
    {
        num_nodes = 0;
    }

    void showNodes()
    {
        string abc = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

        for (int i = 0; i < num_nodes; i++)
        {
            cout << abc[i] << " ";
        }
        cout << endl;
    }

    char IntToChar(int num) {

        if (num > 27 || num < 0) {

            cout << "nodo invalido" << endl;
            return '0';
        }

        string abc = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
        return abc[num];

    }

    void readFile(string file_name)
    {
        ifstream arch(file_name);

        if (!arch.is_open())
        {
            cout << "Error en la apertura del archivo, verificar el nombre del archivo" << endl;
            return;
        }

        arch >> num_nodes;
        adjacency_matrix.resize(num_nodes, vector<int>(num_nodes, 0));

        for (int i = 0; i < num_nodes; ++i)
        {
            for (int j = 0; j < num_nodes; ++j)
            {
                arch >> adjacency_matrix[i][j];
            }
        }

        arch.close();
    }

    void askNode()
    {
        showNodes();
        int nodeNumeric = -1;
        do {
            char node;
            cout << "¿A que nodo quieres ir? ";
            cin >> node;

            // Convertimos el nodo a mayúsculas por si el usuario ingresa una letra minúscula
            node = toupper(node);

            string abc = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
             
            bool flag = false;

            // Buscamos el índice del nodo ingresado
            for (int i = 0; i < num_nodes; i++) {
                if (abc[i] == node) {
                    nodeNumeric = i;
                    flag = true;
                    break; // Salimos del bucle si encontramos el nodo
                }
            }

            // Validamos si el nodo existe
            if (flag == false || nodeNumeric >= num_nodes || nodeNumeric == -1) {
                cout << "El nodo no existe o no es valido. Por favor, ingrese un nodo valido." << endl;
            } else {
                
                break; // Salimos del bucle si el nodo es válido
            }

        } while (true);

        

        dijkstra(0, nodeNumeric); // sabemos que el nodo de inicio siempre sera 0
    }

    vector<int> buildShortestPath(int destino, vector<int> &prev)
    {
        vector<int> camino;
        for (int at = destino; at != -1; at = prev[at])
        {
            camino.push_back(at);
        }
        reverse(camino.begin(), camino.end());
        return camino;
    }

    int minVal(vector<int> &value, vector<bool> &processed)
    {
        int minimum = INT_MAX;
        int vertex = -1;
        for (int i = 0; i < num_nodes; ++i)
        {
            if (!processed[i] && value[i] < minimum)
            {
                vertex = i;
                minimum = value[i];
            }
        }
        return vertex;
    }

    void dijkstra(int start, int end)
    {
        /*
        vector<int> dist(num_nodes, INT_MAX);
        vector<int> prev(num_nodes, -1);
        dist[start] = 0;

        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

        pq.push({0, start});

        while (!pq.empty())
        {
            int u = pq.top().second;

            pq.pop();

            if (u == end)
                break;

            for (int v = 0; v < num_nodes; ++v)
            {
                if (adjacency_matrix[u][v] != 0)
                {
                    int alt = dist[u] + adjacency_matrix[u][v];
                    if (alt < dist[v])
                    {
                        dist[v] = alt;
                        prev[v] = u;
                        pq.push({dist[v], v});
                    }
                }
            }
        }

        printPath(prev, end);
        cout << "Costo total: " << dist[end] << endl;

        */

        vector<int> dist(num_nodes, INT_MAX);
        vector<int> prev(num_nodes, -1);
        vector<bool> processed(num_nodes, false);
        dist[start] = 0;

        for (int i = 0; i < num_nodes - 1; ++i)
        {
            int u = minVal(dist, processed);
            if (u == -1)
                break;
            processed[u] = true;

            for (int v = 0; v < num_nodes; ++v)
            {
                if (adjacency_matrix[u][v] != 0 && !processed[v])
                {
                    int nuevaDistancia = dist[u] + adjacency_matrix[u][v];
                    if (nuevaDistancia < dist[v])
                    {
                        dist[v] = nuevaDistancia;
                        prev[v] = u;
                    }
                }
            }
        }

        if (dist[end] == INT_MAX)
        {
            cout << "No existe un camino hacia el nodo " << IntToChar(end) << "." << endl; // *****
        }
        else
        {
            vector<int> camino = buildShortestPath(end, prev);
            cout << "Camino mas corto: ";
            for (size_t i = 0; i < camino.size(); ++i)
            {
                cout << static_cast<char>('A' + camino[i]);
                if (i != camino.size() - 1)
                    cout << " -> ";
            }
            cout << endl;
            cout << "Costo total: " << dist[end] << endl;
        }
    }

    void printPath(vector<int> &prev, int node)
    {

        string abc = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

        if (prev[node] != -1)
        {
            printPath(prev, prev[node]);
        }

        cout << abc[node] << " -> ";
    }

    // funcion que printea la matriz
    void printMatrix()
    {
        for (int i = 0; i < num_nodes; i++)
        {
            for (int j = 0; j < num_nodes; j++) {
                cout << adjacency_matrix[i][j] << " ";
            }
            cout << endl;
        }
    }
};

int main()
{
    Graph *graph = new Graph();
    //string file_name; //(activar esta linea si se quiere que el usuario ingrese el nombre del archivo)
    
    // generamos nuestra matriz
    string file_name = "matrixTest.txt";

    //cout << "Nombre del archivo" << endl; //(activar esta linea si se quiere que el usuario ingrese el nombre del archivo)
    //cout << ">"; //(activar esta linea si se quiere que el usuario ingrese el nombre del archivo)
    // cin >> file_name; //(activar esta linea si se quiere que el usuario ingrese el nombre del archivo)

    graph->readFile(file_name);

    if (graph->num_nodes == 0) {
        cout << "No se pudo cargar el grafo. Finalizando programa ..." << endl;
        return 0;
    }

    // Preguntamos al usuario a que nodo quiere ir
    graph->askNode();

    delete graph;
    return 0;
}

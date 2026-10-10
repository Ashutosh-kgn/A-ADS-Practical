#include <iostream>
#include <algorithm>
using namespace std;

struct Edge{
    int src, dest, weight;
};

bool compare(Edge a, Edge b){
    return a.weight < b.weight;
}

int findParent(int parent[], int v){
    if (parent[v] == v)
        return v;
    return parent[v] = findParent(parent, parent[v]);
}

void unionSet(int parent[], int rank[], int u, int v){
    int rootU = findParent(parent, u);
    int rootV = findParent(parent, v);

    if (rank[rootU] < rank[rootV])
        parent[rootU] = rootV;
    else if (rank[rootU] > rank[rootV])
        parent[rootV] = rootU;
    else{
        parent[rootV] = rootU;
        rank[rootU]++;
    }
}

int main(){
    int V, E;
    cout << "Enter number of vertices: ";
    cin >> V;
    cout << "Enter number of edges: ";
    cin >> E;
    Edge edges[E];
    cout << "Enter source, destination and weight of each edge:\n";
    for (int i = 0; i < E; i++){
        cin >> edges[i].src
            >> edges[i].dest
            >> edges[i].weight;
    }
    sort(edges, edges + E, compare);
    int parent[V];
    int rank[V] = {0};

    for (int i = 0; i < V; i++)
        parent[i] = i;

    int totalWeight = 0;
    int count = 0;

    cout << "\nEdges in Minimum Spanning Tree:\n";
    for (int i = 0; i < E && count < V - 1; i++){
        int u = edges[i].src;
        int v = edges[i].dest;

        int rootU = findParent(parent, u);
        int rootV = findParent(parent, v);

        if (rootU != rootV){
            cout << u << " - " << v<< " : " << edges[i].weight << endl;
            totalWeight += edges[i].weight;
            unionSet(parent, rank, u, v);
            count++;
        }
    }

    if (count != V - 1)
        cout << "MST does not exist because the graph is disconnected.\n";
    else
        cout << "Total weight of MST: " << totalWeight << endl;
    return 0;
}
/* Madhav Verma
25/DA/039*/

#include <bits/stdc++.h>
using namespace std;

int timer = 0;

void DFS(int u, int parent, vector<vector<int>>& adj,
         vector<int>& visited, vector<int>& tin,
         vector<int>& low, vector<int>& isArticulation) {

    visited[u] = 1;
    tin[u] = low[u] = timer++;
    int children = 0;

    for (int v : adj[u]) {
        if (v == parent)
            continue;

        if (visited[v]) {
            low[u] = min(low[u], tin[v]);
        } else {
            DFS(v, u, adj, visited, tin, low, isArticulation);
            low[u] = min(low[u], low[v]);

            if (parent != -1 && low[v] >= tin[u])
                isArticulation[u] = 1;

            children++;
        }
    }

    if (parent == -1 && children > 1)
        isArticulation[u] = 1;
}

int main() {
    int V = 5;

    vector<vector<int>> edges = {
        {0, 1},
        {1, 2},
        {1, 3},
        {3, 4}
    };

    vector<vector<int>> adj(V);

    for (auto edge : edges) {
        adj[edge[0]].push_back(edge[1]);
        adj[edge[1]].push_back(edge[0]);
    }

    vector<int> visited(V, 0);
    vector<int> tin(V), low(V);
    vector<int> isArticulation(V, 0);

    for (int i = 0; i < V; i++) {
        if (!visited[i])
            DFS(i, -1, adj, visited, tin, low, isArticulation);
    }

    cout << "Articulation Points: ";

    for (int i = 0; i < V; i++) {
        if (isArticulation[i])
            cout << i << " ";
    }

    return 0;
}

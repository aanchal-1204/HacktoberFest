#include <iostream>
#include <vector>
#include <queue>
#include <limits>

using namespace std;

const int INF = numeric_limits<int>::max();

void dijkstra(int start, const vector<vector<pair<int, int>>> &graph, vector<int> &dist) {
    int n = graph.size();
    dist.assign(n, INF);
    dist[start] = 0;

    // Priority queue to store (distance, vertex) and process smallest distance first
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;
    pq.emplace(0, start);

    while (!pq.empty()) {
        int uDist = pq.top().first;
        int u = pq.top().second;
        pq.pop();

        // Skip processing if we have found a better distance
        if (uDist > dist[u]) continue;

        for (const auto &edge : graph[u]) {
            int v = edge.first;
            int weight = edge.second;

            // Relaxation step
            if (dist[u] + weight < dist[v]) {
                dist[v] = dist[u] + weight;
                pq.emplace(dist[v], v);
            }
        }
    }
}

int main() {
    int V, E;
    cout << "Enter number of vertices and edges: ";
    cin >> V >> E;

    vector<vector<pair<int, int>>> graph(V);
    
    cout << "Enter edges (u v weight) with vertices starting from 0:\n";
    for (int i = 0; i < E; ++i) {
        int u, v, weight;
        cin >> u >> v >> weight;
        graph[u].emplace_back(v, weight);
        graph[v].emplace_back(u, weight); // Uncomment this line for an undirected graph
    }

    int start;
    cout << "Enter start vertex: ";
    cin >> start;

    vector<int> dist;
    dijkstra(start, graph, dist);

    cout << "Shortest distances from vertex " << start << ":\n";
    for (int i = 0; i < V; ++i) {
        if (dist[i] == INF) {
            cout << "Vertex " << i << ": unreachable\n";
        } else {
            cout << "Vertex " << i << ": " << dist[i] << "\n";
        }
    }

    return 0;
}

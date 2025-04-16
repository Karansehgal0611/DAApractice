#include <iostream>
#include <vector>
#include <climits>

using namespace std;

// a structure to represent a weighted edge in a graph
struct Edge {
    int src, dest, weight;
};

// a structure to represent a connected, directed, and weighted graph
struct Graph {
    int V, E;
    vector<Edge> edges;
};

// The main function that finds shortest distances from src
// to all other vertices using the Bellman-Ford algorithm. The
// function also detects negative weight cycles
void BellmanFord(Graph& graph, int src) {
    int V = graph.V;
    int E = graph.E;
    vector<int> dist(V, INT_MAX);
    dist[src] = 0;

    // Relax all edges V-1 times
    for (int i = 0; i < V - 1; i++) {
        for (int j = 0; j < E; j++) {
            int u = graph.edges[j].src;
            int v = graph.edges[j].dest;
            int weight = graph.edges[j].weight;
            if (dist[u] != INT_MAX && dist[u] + weight < dist[v]) {
                dist[v] = dist[u] + weight;
            }
        }
    }

    // Check for negative-weight cycles
    for (int i = 0; i < E; i++) {
        int u = graph.edges[i].src;
        int v = graph.edges[i].dest;
        int weight = graph.edges[i].weight;
        if (dist[u] != INT_MAX && dist[u] + weight < dist[v]) {
            cout << "Graph contains negative weight cycle\n";
            return;
        }
    }

    // Print the distances
    cout << "Vertex Distance from Source\n";
    for (int i = 0; i < V; i++) {
        cout << i << "\t\t" << dist[i] << endl;
    }
}

int main() {
    int V, E;
    cout << "Enter the number of vertices: ";
    cin >> V;
    cout << "Enter the number of edges: ";
    cin >> E;

    Graph graph;
    graph.V = V;
    graph.E = E;

    cout << "Enter source, destination, and weight for each edge:\n";
    for (int i = 0; i < E; i++) {
        Edge edge;
        cin >> edge.src >> edge.dest >> edge.weight;
        graph.edges.push_back(edge);
    }

    BellmanFord(graph, 0);

    return 0;
}

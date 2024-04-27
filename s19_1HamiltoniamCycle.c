#include <stdio.h>
#include <stdbool.h>

#define V 5 // Number of vertices in the graph

// Function to check if the current vertex can be added to the Hamiltonian cycle
bool isSafe(int v, bool graph[V][V], int path[], int pos) {
    // Check if this vertex is adjacent to the previously added vertex
    if (graph[path[pos - 1]][v] == false)
        return false;

    // Check if this vertex has already been added to the path
    for (int i = 0; i < pos; i++)
        if (path[i] == v)
            return false;

    return true;
}

// Function to recursively find Hamiltonian cycle starting from the current vertex
bool hamCycleUtil(bool graph[V][V], int path[], int pos) {
    // Base case: if all vertices are included in the path
    if (pos == V) {
        // Check if there is an edge from the last added vertex to the first vertex
        if (graph[path[pos - 1]][path[0]] == true)
            return true;
        else
            return false;
    }

    // Try different vertices as the next vertex in the path
    for (int v = 1; v < V; v++) {
        if (isSafe(v, graph, path, pos)) {
            path[pos] = v;

            // Recur to construct the rest of the path
            if (hamCycleUtil(graph, path, pos + 1) == true)
                return true;

            // If adding vertex v doesn't lead to a solution, remove it from the path
            path[pos] = -1;
        }
    }

    return false;
}

// Function to find Hamiltonian cycle in the given graph
bool hamCycle(bool graph[V][V]) {
    int path[V];
    for (int i = 0; i < V; i++)
        path[i] = -1;

    // Starting from vertex 0 as the initial vertex
    path[0] = 0;

    if (hamCycleUtil(graph, path, 1) == false) {
        printf("The graph does not contain a Hamiltonian cycle\n");
        return false;
    }

    printf("The graph contains a Hamiltonian cycle: ");
    for (int i = 0; i < V; i++)
        printf("%d ", path[i]);
    printf("%d\n", path[0]);
    return true;
}

// Main function
int main() {
    bool graph[V][V] = {
        {0, 1, 0, 1, 0},
        {1, 0, 1, 1, 1},
        {0, 1, 0, 0, 1},
        {1, 1, 0, 0, 1},
        {0, 1, 1, 1, 0}
    };

    // Check if the graph contains a Hamiltonian cycle
    hamCycle(graph);

    return 0;
}

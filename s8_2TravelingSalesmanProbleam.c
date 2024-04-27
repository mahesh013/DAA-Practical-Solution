#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>

#define V 4 // Number of vertices

// Function to find the nearest neighbor of a given vertex
int nearestNeighbor(int graph[V][V], int v, bool visited[]) {
    int minDistance = INT_MAX;
    int nearestVertex;

    // Find the nearest neighbor that has not been visited
    for (int i = 0; i < V; i++) {
        if (graph[v][i] < minDistance && !visited[i]) {
            minDistance = graph[v][i];
            nearestVertex = i;
        }
    }

    return nearestVertex;
}

// Function to find the minimum cost Hamiltonian cycle using the nearest neighbor algorithm
void nearestNeighborTSP(int graph[V][V]) {
    bool visited[V]; // Array to keep track of visited vertices
    for (int i = 0; i < V; i++) {
        visited[i] = false; // Initialize all vertices as not visited
    }

    int path[V]; // Array to store the minimum cost Hamiltonian cycle
    int currentVertex = 0; // Start from the first vertex
    visited[currentVertex] = true; // Mark the first vertex as visited
    path[0] = currentVertex;

    // Find the nearest neighbor for each vertex
    for (int i = 1; i < V; i++) {
        int nearest = nearestNeighbor(graph, currentVertex, visited);
        path[i] = nearest;
        visited[nearest] = true;
        currentVertex = nearest;
    }

    // Print the minimum cost Hamiltonian cycle
    printf("Minimum Cost Hamiltonian Cycle: ");
    for (int i = 0; i < V; i++) {
        printf("%d ", path[i]);
    }
    printf("%d\n", path[0]); // Return to the starting vertex to complete the cycle
}

int main() {
    // Example graph represented using adjacency matrix
    int graph[V][V] = {
        {0, 10, 15, 20},
        {10, 0, 35, 25},
        {15, 35, 0, 30},
        {20, 25, 30, 0}
    };

    // Find the minimum cost Hamiltonian cycle using the nearest neighbor algorithm
    nearestNeighborTSP(graph);

    return 0;
}

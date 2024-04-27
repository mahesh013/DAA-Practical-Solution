#include <stdio.h>
#include <stdbool.h>

#define V 4 // Number of vertices in the graph

// Function to print the solution (color assignments)
void printSolution(int color[]) {
    printf("Vertex\tColor\n");
    for (int i = 0; i < V; i++)
        printf("%d\t%d\n", i, color[i]);
}

// Function to check if it's safe to assign a color to the current vertex
bool isSafe(int v, bool graph[V][V], int color[], int c) {
    for (int i = 0; i < V; i++)
        if (graph[v][i] && c == color[i])
            return false;
    return true;
}

// Function to assign colors to vertices using the greedy approach
void graphColoring(bool graph[V][V], int m) {
    int color[V];
    for (int i = 0; i < V; i++)
        color[i] = -1;

    // Assign the first color to the first vertex
    color[0] = 0;

    // Assign colors to remaining V-1 vertices
    for (int v = 1; v < V; v++) {
        // Consider all available colors
        bool available[m];
        for (int i = 0; i < m; i++)
            available[i] = true;

        // Check colors of adjacent vertices and mark them as unavailable
        for (int i = 0; i < V; i++)
            if (graph[v][i] && color[i] != -1)
                available[color[i]] = false;

        // Find the first available color
        int c;
        for (c = 0; c < m; c++)
            if (available[c])
                break;

        color[v] = c;
    }

    // Print the solution
    printSolution(color);
}

// Main function
int main() {
    bool graph[V][V] = {
        {0, 1, 1, 1},
        {1, 0, 1, 0},
        {1, 1, 0, 1},
        {1, 0, 1, 0}
    };
    int m = 3; // Number of colors

    printf("Coloring of the graph using %d colors:\n", m);
    graphColoring(graph, m);

    return 0;
}

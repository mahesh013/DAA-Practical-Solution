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
bool graphColoringUtil(bool graph[V][V], int m, int color[], int v) {
    if (v == V)
        return true;

    for (int c = 1; c <= m; c++) {
        if (isSafe(v, graph, color, c)) {
            color[v] = c;
            if (graphColoringUtil(graph, m, color, v + 1) == true)
                return true;
            color[v] = 0;
        }
    }

    return false;
}

// Function to color the graph using the greedy approach
void graphColoring(bool graph[V][V], int m) {
    int color[V];
    for (int i = 0; i < V; i++)
        color[i] = 0;

    if (graphColoringUtil(graph, m, color, 0) == false) {
        printf("Solution does not exist\n");
        return;
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

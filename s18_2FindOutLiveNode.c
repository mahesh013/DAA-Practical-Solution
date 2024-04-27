#include <stdio.h>
#include <stdbool.h>

#define V 6 // Number of vertices in the graph

// Function to find live nodes, E-nodes, and dead nodes from the given graph
void findNodes(int graph[V][V]) {
    bool isLive[V] = {false}; // Array to store whether a node is live or not
    bool isE[V] = {false};    // Array to store whether a node is an E-node or not
    bool isDead[V] = {true};  // Array to store whether a node is dead or not

    // Check for live nodes
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            if (graph[i][j]) {
                isLive[i] = true;
                isDead[j] = false;
            }
        }
    }

    // Check for E-nodes
    for (int i = 0; i < V; i++) {
        if (!isLive[i]) {
            isE[i] = true;
        }
    }

    // Print live nodes
    printf("Live nodes: ");
    for (int i = 0; i < V; i++) {
        if (isLive[i]) {
            printf("%d ", i);
        }
    }
    printf("\n");

    // Print E-nodes
    printf("E-nodes: ");
    for (int i = 0; i < V; i++) {
        if (isE[i]) {
            printf("%d ", i);
        }
    }
    printf("\n");

    // Print dead nodes
    printf("Dead nodes: ");
    for (int i = 0; i < V; i++) {
        if (isDead[i]) {
            printf("%d ", i);
        }
    }
    printf("\n");
}

// Main function
int main() {
    int graph[V][V] = {
        {0, 1, 0, 0, 0, 0},
        {0, 0, 1, 0, 0, 0},
        {0, 0, 0, 1, 0, 0},
        {0, 0, 0, 0, 1, 0},
        {0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 1}
    };

    // Find live nodes, E-nodes, and dead nodes
    findNodes(graph);

    return 0;
}

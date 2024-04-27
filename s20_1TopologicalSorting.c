#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_VERTICES 100 // Maximum number of vertices

// Structure to represent a node in the adjacency list
struct Node {
    int vertex;
    struct Node* next;
};

// Structure to represent the adjacency list
struct Graph {
    int numVertices;
    struct Node** adjList;
};

// Function to create a new node
struct Node* createNode(int v) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->vertex = v;
    newNode->next = NULL;
    return newNode;
}

// Function to create a graph with a given number of vertices
struct Graph* createGraph(int numVertices) {
    struct Graph* graph = (struct Graph*)malloc(sizeof(struct Graph));
    graph->numVertices = numVertices;
    graph->adjList = (struct Node**)malloc(numVertices * sizeof(struct Node*));
    for (int i = 0; i < numVertices; i++) {
        graph->adjList[i] = NULL;
    }
    return graph;
}

// Function to add an edge to the graph
void addEdge(struct Graph* graph, int src, int dest) {
    struct Node* newNode = createNode(dest);
    newNode->next = graph->adjList[src];
    graph->adjList[src] = newNode;
}

// Function to perform DFS traversal of the graph
void topologicalSortUtil(struct Graph* graph, int v, bool visited[], int* stackIndex, int stack[]) {
    visited[v] = true;

    // Recur for all the vertices adjacent to this vertex
    struct Node* temp = graph->adjList[v];
    while (temp != NULL) {
        if (!visited[temp->vertex]) {
            topologicalSortUtil(graph, temp->vertex, visited, stackIndex, stack);
        }
        temp = temp->next;
    }

    // Push the current vertex onto the stack
    stack[++(*stackIndex)] = v;
}

// Function to perform topological sorting of the graph
void topologicalSort(struct Graph* graph) {
    int stack[MAX_VERTICES];
    int stackIndex = -1;
    bool visited[MAX_VERTICES];

    // Mark all the vertices as not visited
    for (int i = 0; i < graph->numVertices; i++) {
        visited[i] = false;
    }

    // Call the recursive helper function to store topological sort starting from all vertices
    for (int i = 0; i < graph->numVertices; i++) {
        if (!visited[i]) {
            topologicalSortUtil(graph, i, visited, &stackIndex, stack);
        }
    }

    // Print the vertices in topological order
    printf("Topological sorting of the graph: ");
    while (stackIndex >= 0) {
        printf("%d ", stack[stackIndex--]);
    }
    printf("\n");
}

// Main function
int main() {
    // Create a graph
    struct Graph* graph = createGraph(6);
    addEdge(graph, 5, 2);
    addEdge(graph, 5, 0);
    addEdge(graph, 4, 0);
    addEdge(graph, 4, 1);
    addEdge(graph, 2, 3);
    addEdge(graph, 3, 1);

    // Perform topological sorting
    topologicalSort(graph);

    return 0;
}

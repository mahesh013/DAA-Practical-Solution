#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_SIZE 100

// Structure to represent an adjacency list node
struct AdjListNode {
    int dest; // Destination vertex
    struct AdjListNode* next; // Pointer to the next node
};

// Structure to represent an adjacency list
struct AdjList {
    struct AdjListNode* head; // Pointer to the head of the list
};

// Structure to represent a graph
struct Graph {
    int V; // Number of vertices
    struct AdjList* array; // Array of adjacency lists
};

// Function to create a new adjacency list node
struct AdjListNode* newAdjListNode(int dest) {
    struct AdjListNode* newNode = (struct AdjListNode*)malloc(sizeof(struct AdjListNode));
    newNode->dest = dest;
    newNode->next = NULL;
    return newNode;
}

// Function to create a graph with V vertices
struct Graph* createGraph(int V) {
    struct Graph* graph = (struct Graph*)malloc(sizeof(struct Graph));
    graph->V = V;
    graph->array = (struct AdjList*)malloc(V * sizeof(struct AdjList));
    for (int i = 0; i < V; ++i) {
        graph->array[i].head = NULL;
    }
    return graph;
}

// Function to add an edge to the graph
void addEdge(struct Graph* graph, int src, int dest) {
    struct AdjListNode* newNode = newAdjListNode(dest);
    newNode->next = graph->array[src].head;
    graph->array[src].head = newNode;
}

// Depth First Search (DFS) function
void DFSUtil(struct Graph* graph, int v, bool visited[]) {
    visited[v] = true;
    printf("%d ", v);

    struct AdjListNode* temp = graph->array[v].head;
    while (temp != NULL) {
        if (!visited[temp->dest]) {
            DFSUtil(graph, temp->dest, visited);
        }
        temp = temp->next;
    }
}

// Function to perform Depth First Search (DFS) traversal
void DFS(struct Graph* graph, int start) {
    bool* visited = (bool*)malloc(graph->V * sizeof(bool));
    for (int i = 0; i < graph->V; ++i) {
        visited[i] = false;
    }

    printf("Depth First Search (DFS) starting from vertex %d: ", start);
    DFSUtil(graph, start, visited);
    printf("\n");

    free(visited);
}

int main() {
    int V = 5; // Number of vertices
    struct Graph* graph = createGraph(V);

    // Adding edges to the graph
    addEdge(graph, 0, 1);
    addEdge(graph, 0, 2);
    addEdge(graph, 1, 2);
    addEdge(graph, 1, 3);
    addEdge(graph, 2, 3);
    addEdge(graph, 3, 4);

    // Perform DFS traversal starting from vertex 0
    DFS(graph, 0);

    return 0;
}

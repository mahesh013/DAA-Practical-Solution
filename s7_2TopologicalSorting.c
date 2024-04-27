#include <stdio.h>
#include <stdlib.h>

// Structure to represent a node in the graph
struct Node {
    int data;
    struct Node* next;
};

// Structure to represent the graph
struct Graph {
    int V; // Number of vertices
    struct Node** adjList; // Adjacency list
};

// Function to create a new node
struct Node* createNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

// Function to create a graph with V vertices
struct Graph* createGraph(int V) {
    struct Graph* graph = (struct Graph*)malloc(sizeof(struct Graph));
    graph->V = V;
    graph->adjList = (struct Node**)malloc(V * sizeof(struct Node*));
    for (int i = 0; i < V; ++i) {
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

// Function to perform topological sorting
void topologicalSortUtil(int v, struct Graph* graph, int visited[], struct Node** stack) {
    visited[v] = 1; // Mark the current node as visited

    struct Node* temp = graph->adjList[v]; // Traverse all adjacent vertices of the current vertex
    while (temp != NULL) {
        if (!visited[temp->data]) { // If adjacent vertex is not visited, recursively call topologicalSortUtil
            topologicalSortUtil(temp->data, graph, visited, stack);
        }
        temp = temp->next;
    }

    // Push the current vertex to the stack which stores the result
    struct Node* newNode = createNode(v);
    newNode->next = *stack;
    *stack = newNode;
}

// Function to perform topological sorting
void topologicalSort(struct Graph* graph) {
    int visited[graph->V];
    struct Node* stack = NULL; // Create a stack to store the topological sorting result

    // Mark all the vertices as not visited
    for (int i = 0; i < graph->V; i++) {
        visited[i] = 0;
    }

    // Call the recursive helper function to store topological sorting starting from all vertices one by one
    for (int i = 0; i < graph->V; i++) {
        if (!visited[i]) {
            topologicalSortUtil(i, graph, visited, &stack);
        }
    }

    // Print contents of stack
    while (stack != NULL) {
        printf("%d ", stack->data);
        struct Node* temp = stack;
        stack = stack->next;
        free(temp);
    }
}

int main() {
    // Example graph represented using adjacency list
    int V = 6;
    struct Graph* graph = createGraph(V);
    addEdge(graph, 5, 2);
    addEdge(graph, 5, 0);
    addEdge(graph, 4, 0);
    addEdge(graph, 4, 1);
    addEdge(graph, 2, 3);
    addEdge(graph, 3, 1);

    printf("Topological sorting of the graph: ");
    topologicalSort(graph);

    return 0;
}

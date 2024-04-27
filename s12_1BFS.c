#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_SIZE 100

// Structure to represent a queue node
struct QueueNode {
    int data; // Data of the node
    struct QueueNode* next; // Pointer to the next node in the queue
};

// Structure to represent a queue
struct Queue {
    struct QueueNode *front, *rear; // Front and rear pointers of the queue
};

// Function to create a new queue node
struct QueueNode* newQueueNode(int data) {
    struct QueueNode* temp = (struct QueueNode*)malloc(sizeof(struct QueueNode));
    temp->data = data;
    temp->next = NULL;
    return temp;
}

// Function to create a new queue
struct Queue* createQueue() {
    struct Queue* queue = (struct Queue*)malloc(sizeof(struct Queue));
    queue->front = queue->rear = NULL;
    return queue;
}

// Function to check if the queue is empty
bool isEmpty(struct Queue* queue) {
    return queue->front == NULL;
}

// Function to enqueue a node to the queue
void enqueue(struct Queue* queue, int data) {
    struct QueueNode* temp = newQueueNode(data);
    if (isEmpty(queue)) {
        queue->front = queue->rear = temp;
        return;
    }
    queue->rear->next = temp;
    queue->rear = temp;
}

// Function to dequeue a node from the queue
int dequeue(struct Queue* queue) {
    if (isEmpty(queue)) {
        return -1;
    }
    struct QueueNode* temp = queue->front;
    int data = temp->data;
    queue->front = queue->front->next;
    free(temp);
    return data;
}

// Structure to represent a graph node
struct GraphNode {
    int data; // Data of the node
    struct GraphNode* next; // Pointer to the next node in the adjacency list
};

// Structure to represent a graph
struct Graph {
    int V; // Number of vertices in the graph
    struct GraphNode** adjList; // Array of adjacency lists
    bool* visited; // Array to keep track of visited vertices
};

// Function to create a new graph node
struct GraphNode* newGraphNode(int data) {
    struct GraphNode* temp = (struct GraphNode*)malloc(sizeof(struct GraphNode));
    temp->data = data;
    temp->next = NULL;
    return temp;
}

// Function to create a graph with V vertices
struct Graph* createGraph(int V) {
    struct Graph* graph = (struct Graph*)malloc(sizeof(struct Graph));
    graph->V = V;
    graph->adjList = (struct GraphNode**)malloc(V * sizeof(struct GraphNode*));
    graph->visited = (bool*)malloc(V * sizeof(bool));
    for (int i = 0; i < V; ++i) {
        graph->adjList[i] = NULL;
        graph->visited[i] = false;
    }
    return graph;
}

// Function to add an edge to the graph
void addEdge(struct Graph* graph, int src, int dest) {
    struct GraphNode* newNode = newGraphNode(dest);
    newNode->next = graph->adjList[src];
    graph->adjList[src] = newNode;

    newNode = newGraphNode(src);
    newNode->next = graph->adjList[dest];
    graph->adjList[dest] = newNode;
}

// Function to perform Breadth First Search (BFS) traversal
void BFS(struct Graph* graph, int start) {
    struct Queue* queue = createQueue();

    // Mark the current node as visited and enqueue it
    graph->visited[start] = true;
    enqueue(queue, start);

    printf("Breadth First Search (BFS) starting from vertex %d: ", start);

    while (!isEmpty(queue)) {
        // Dequeue a vertex from the queue and print it
        int current = dequeue(queue);
        printf("%d ", current);

        // Get all adjacent vertices of the dequeued vertex current. If an adjacent vertex has not been visited yet, mark it visited and enqueue it
        struct GraphNode* temp = graph->adjList[current];
        while (temp != NULL) {
            int adj = temp->data;
            if (!graph->visited[adj]) {
                graph->visited[adj] = true;
                enqueue(queue, adj);
            }
            temp = temp->next;
        }
    }

    printf("\n");

    free(queue);
}

int main() {
    int V = 5; // Number of vertices
    struct Graph* graph = createGraph(V);

    // Adding edges to the graph
    addEdge(graph, 0, 1);
    addEdge(graph, 0, 2);
    addEdge(graph, 1, 3);
    addEdge(graph, 1, 4);
    addEdge(graph, 2, 3);

    // Perform BFS traversal starting from vertex 0
    BFS(graph, 0);

    return 0;
}

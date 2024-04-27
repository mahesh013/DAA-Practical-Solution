#include <stdio.h>
#include <stdlib.h>

#define MAX_ITEMS 100

// Structure to represent an item
struct Item {
    int weight; // Weight of the item
    int value;  // Value of the item
};

// Structure to represent a node of the search tree
struct Node {
    int level;          // Level of the node in the search tree
    int profit;         // Profit of the node
    int weight;         // Weight of the node
    float bound;        // Bound of the node
};

// Comparison function to sort items based on their ratio of value to weight in non-increasing order
int compare(const void* a, const void* b) {
    double ratio1 = (double)(((struct Item*)b)->value) / ((struct Item*)b)->weight;
    double ratio2 = (double)(((struct Item*)a)->value) / ((struct Item*)a)->weight;
    return ratio1 > ratio2;
}

// Function to calculate the bound of a node
float bound(struct Node u, int n, int W, struct Item arr[]) {
    if (u.weight >= W) {
        return 0;
    }
    float profit_bound = u.profit;
    int j = u.level + 1;
    int totweight = u.weight;

    while ((j < n) && (totweight + arr[j].weight <= W)) {
        totweight += arr[j].weight;
        profit_bound += arr[j].value;
        j++;
    }
    if (j < n) {
        profit_bound += (W - totweight) * ((double)arr[j].value / arr[j].weight);
    }
    return profit_bound;
}

// Function to solve 0/1 knapsack problem using LCBB
int knapsackLCBB(int W, struct Item arr[], int n) {
    // Sort the items based on their value to weight ratio in non-increasing order
    qsort(arr, n, sizeof(arr[0]), compare);

    struct Node u, v;
    u.level = -1;
    u.profit = u.weight = 0;
    u.bound = bound(u, n, W, arr);
    
    int maxProfit = 0;

    // Create a queue for the nodes of the search tree
    int front = -1, rear = -1;
    struct Node* Q = (struct Node*)malloc(MAX_ITEMS * sizeof(struct Node));

    // Add the root node to the queue
    Q[++rear] = u;

    // Loop through the search tree until all nodes are explored
    while (front != rear) {
        // Remove the front node from the queue
        u = Q[++front];

        // If the node has a better bound than the current max profit, explore its children
        if (u.bound > maxProfit) {
            v.level = u.level + 1;
            v.weight = u.weight + arr[v.level].weight;
            v.profit = u.profit + arr[v.level].value;

            // If the child node is feasible and has a higher profit than the current max profit, update the max profit
            if (v.weight <= W && v.profit > maxProfit) {
                maxProfit = v.profit;
            }

            v.bound = bound(v, n, W, arr);

            // If the child node has a bound higher than the current max profit, add it to the queue
            if (v.bound > maxProfit) {
                Q[++rear] = v;
            }

            // Explore the other child node without including the current item
            v.weight = u.weight;
            v.profit = u.profit;
            v.bound = bound(v, n, W, arr);

            // If the child node has a bound higher than the current max profit, add it to the queue
            if (v.bound > maxProfit) {
                Q[++rear] = v;
            }
        }
    }

    free(Q);
    return maxProfit;
}

int main() {
    int W = 50; // Knapsack capacity
    struct Item arr[] = {{10, 60}, {20, 100}, {30, 120}}; // Items (weight, value)
    int n = sizeof(arr) / sizeof(arr[0]); // Number of items

    int maxProfit = knapsackLCBB(W, arr, n);
    printf("Maximum profit: %d\n", maxProfit);

    return 0;
}

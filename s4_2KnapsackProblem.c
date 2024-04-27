#include <stdio.h>
#include <stdlib.h>

// Structure to represent an item
struct Item {
    int value; // Value of the item
    int weight; // Weight of the item
};

// Comparison function to sort items based on their value per unit weight (value/weight)
int compare(const void* a, const void* b) {
    double ratioA = ((struct Item*)a)->value / (double)((struct Item*)a)->weight;
    double ratioB = ((struct Item*)b)->value / (double)((struct Item*)b)->weight;
    return ratioB - ratioA; // Sort in descending order of value per unit weight
}

// Function to solve fractional knapsack problem using greedy approach
double fractionalKnapsack(int capacity, struct Item arr[], int n) {
    // Sort items based on their value per unit weight
    qsort(arr, n, sizeof(struct Item), compare);

    double totalValue = 0.0; // Total value of items selected

    // Iterate through sorted items and select items greedily
    for (int i = 0; i < n; i++) {
        if (capacity >= arr[i].weight) {
            // If item can be selected completely
            totalValue += arr[i].value;
            capacity -= arr[i].weight;
        } else {
            // If only a fraction of the item can be selected
            totalValue += (arr[i].value / (double)arr[i].weight) * capacity;
            break; // Knapsack is full
        }
    }

    return totalValue;
}

int main() {
    // Example data
    int capacity = 50; // Capacity of the knapsack
    struct Item arr[] = {{60, 10}, {100, 20}, {120, 30}}; // Array of items with their values and weights
    int n = sizeof(arr) / sizeof(arr[0]); // Number of items

    double maxValue = fractionalKnapsack(capacity, arr, n);

    printf("Maximum value that can be obtained: %.2f\n", maxValue);

    return 0;
}

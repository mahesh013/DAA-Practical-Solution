#include <stdio.h>
#include <stdlib.h>

// Structure to represent an item
struct Item {
    int value; // Value of the item
    int weight; // Weight of the item
    double ratio; // Value-to-weight ratio of the item
};

// Comparison function to sort items based on their value-to-weight ratio in non-increasing order
int compare(const void* a, const void* b) {
    struct Item* item1 = (struct Item*)a;
    struct Item* item2 = (struct Item*)b;
    return (item2->ratio - item1->ratio) > 0 ? 1 : -1;
}

// Function to find maximum value obtained by filling the knapsack with fractional items
double fractionalKnapsack(int W, struct Item arr[], int n) {
    // Sort items based on their value-to-weight ratio
    qsort(arr, n, sizeof(struct Item), compare);

    double totalValue = 0.0; // Total value of items selected
    int currentWeight = 0; // Current weight in the knapsack

    // Loop through all items and add them to the knapsack fractionally
    for (int i = 0; i < n; i++) {
        // If adding the entire item does not exceed the capacity, add it completely
        if (currentWeight + arr[i].weight <= W) {
            totalValue += arr[i].value;
            currentWeight += arr[i].weight;
        } else {
            // Add fraction of the item
            int remainingWeight = W - currentWeight;
            totalValue += arr[i].ratio * remainingWeight;
            break; // Knapsack is full
        }
    }

    return totalValue;
}

int main() {
    // Example data
    int W = 50; // Capacity of the knapsack
    struct Item arr[] = {{60, 10}, {100, 20}, {120, 30}}; // Array of items with their values and weights
    int n = sizeof(arr) / sizeof(arr[0]); // Number of items

    // Calculate the maximum value obtained
    double maxValue = fractionalKnapsack(W, arr, n);

    // Print the maximum value obtained
    printf("Maximum value that can be obtained: %.2f\n", maxValue);

    return 0;
}

#include <stdio.h>
#include <limits.h>

// Function to find the minimum of two integers
int min(int a, int b) {
    return (a < b) ? a : b;
}

// Function to construct an optimal binary search tree
int optimalBST(int keys[], int freq[], int n) {
    // Create a table to store the cost of searching keys[i] to keys[j]
    int cost[n][n];

    // Initialize the table with 0
    for (int i = 0; i < n; i++) {
        cost[i][i] = freq[i];
    }

    // Fill the table in bottom-up manner
    for (int L = 2; L <= n; L++) {
        for (int i = 0; i <= n - L + 1; i++) {
            int j = i + L - 1;
            cost[i][j] = INT_MAX;

            // Try making all keys in the range keys[i] to keys[j] as root one by one and find the minimum cost
            for (int r = i; r <= j; r++) {
                int c = ((r > i) ? cost[i][r - 1] : 0) + ((r < j) ? cost[r + 1][j] : 0) + 0;
                cost[i][j] = min(cost[i][j], c);
            }
        }
    }

    // Return the cost of searching the entire range of keys
    return cost[0][n - 1];
}

int main() {
    int keys[] = {10, 12, 20};
    int freq[] = {34, 8, 50};
    int n = sizeof(keys) / sizeof(keys[0]);

    printf("The cost of the optimal BST is %d\n", optimalBST(keys, freq, n));

    return 0;
}

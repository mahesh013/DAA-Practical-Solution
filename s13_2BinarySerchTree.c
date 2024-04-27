#include <stdio.h>
#include <limits.h>

#define MAX_KEYS 10

// Function to calculate the sum of frequencies of keys from i to j
int sum(int freq[], int i, int j) {
    int s = 0;
    for (int k = i; k <= j; k++) {
        s += freq[k];
    }
    return s;
}

// Function to construct an optimal binary search tree
int optimalBST(int keys[], int freq[], int n) {
    int cost[n + 1][n + 1]; // cost[i][j] will store the cost of the optimal binary search tree containing keys[i] to keys[j]
    
    // Initialize cost table
    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= n; j++) {
            cost[i][j] = 0;
        }
    }

    // For a single key, the cost is equal to the frequency of the key
    for (int i = 0; i < n; i++) {
        cost[i][i] = freq[i];
    }

    // Fill the cost table using dynamic programming
    for (int L = 2; L <= n; L++) {
        for (int i = 0; i <= n - L + 1; i++) {
            int j = i + L - 1;
            cost[i][j] = INT_MAX;

            // Try making all keys in the range keys[i..j] as root and find the minimum cost
            for (int r = i; r <= j; r++) {
                int c = ((r > i) ? cost[i][r - 1] : 0) +
                        ((r < j) ? cost[r + 1][j] : 0) +
                        sum(freq, i, j);
                if (c < cost[i][j]) {
                    cost[i][j] = c;
                }
            }
        }
    }

    return cost[0][n - 1];
}

int main() {
    int keys[MAX_KEYS] = {10, 20, 30, 40, 50}; // Sorted keys
    int freq[MAX_KEYS] = {4, 2, 6, 3, 5}; // Frequencies of keys
    int n = sizeof(keys) / sizeof(keys[0]);

    int min_cost = optimalBST(keys, freq, n);
    printf("Minimum cost of optimal binary search tree: %d\n", min_cost);

    return 0;
}

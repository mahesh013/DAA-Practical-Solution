#include <stdio.h>
#include <limits.h>

// Function to find the minimum number of multiplications needed for matrix chain multiplication
int matrixChainOrder(int p[], int n) {
    int m[n][n]; // m[i][j] stores the minimum number of scalar multiplications needed to compute the matrix A[i]A[i+1]...A[j]
    int i, j, k, L, q;

    // Cost is 0 when multiplying one matrix
    for (i = 1; i < n; i++) {
        m[i][i] = 0;
    }

    // L is the chain length
    for (L = 2; L < n; L++) {
        for (i = 1; i < n - L + 1; i++) {
            j = i + L - 1;
            m[i][j] = INT_MAX;
            for (k = i; k <= j - 1; k++) {
                // q = cost/scalar multiplications
                q = m[i][k] + m[k + 1][j] + p[i - 1] * p[k] * p[j];
                if (q < m[i][j]) {
                    m[i][j] = q;
                }
            }
        }
    }

    return m[1][n - 1];
}

int main() {
    int arr[] = {10, 30, 5, 60}; // Matrix dimensions: 10x30, 30x5, 5x60
    int size = sizeof(arr) / sizeof(arr[0]);

    printf("Minimum number of multiplications needed: %d\n", matrixChainOrder(arr, size));

    return 0;
}

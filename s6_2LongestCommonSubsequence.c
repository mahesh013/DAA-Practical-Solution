#include<stdio.h>
#include<string.h>

// Function to find the maximum of two integers
int max(int a, int b) {
    return (a > b) ? a : b;
}

// Function to find the length of the Longest Common Subsequence (LCS)
int lcs_length(char *X, char *Y, int m, int n) {
    int L[m + 1][n + 1];
    int i, j;

    // Build the L[m+1][n+1] table in bottom-up manner
    for (i = 0; i <= m; i++) {
        for (j = 0; j <= n; j++) {
            if (i == 0 || j == 0)
                L[i][j] = 0; // Base case
            else if (X[i - 1] == Y[j - 1])
                L[i][j] = L[i - 1][j - 1] + 1; // Characters match, add 1 to the LCS length
            else
                L[i][j] = max(L[i - 1][j], L[i][j - 1]); // Characters do not match, take the maximum of previous lengths
        }
    }

    return L[m][n]; // Return the length of LCS
}

int main() {
    char X[] = "AGGTAB";
    char Y[] = "GXTXAYB";

    int m = strlen(X);
    int n = strlen(Y);

    printf("Length of Longest Common Subsequence: %d\n", lcs_length(X, Y, m, n));

    return 0;
}

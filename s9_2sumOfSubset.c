#include <stdio.h>
#include <stdbool.h>

// Function to print the subset
void printSubset(int subset[], int size) {
    printf("{ ");
    for (int i = 0; i < size; i++) {
        printf("%d ", subset[i]);
    }
    printf("}\n");
}

// Function to find all subsets with a given sum using backtracking
void findSubsets(int set[], int n, int sum, int subset[], int subsetSize, int currentIndex, int currentSum) {
    if (currentSum == sum) {
        printSubset(subset, subsetSize);
        // Exclude the current element and try finding subsets
        // with the same sum including the current element
        findSubsets(set, n, sum, subset, subsetSize - 1, currentIndex + 1, currentSum - set[currentIndex]);
        return;
    }

    // Include the current element
    for (int i = currentIndex; i < n; i++) {
        subset[subsetSize] = set[i];
        // Recursively find subsets with the remaining sum
        findSubsets(set, n, sum, subset, subsetSize + 1, i + 1, currentSum + set[i]);
    }
}

// Function to find subsets with a given sum
void findSubsetsWithSum(int set[], int n, int sum) {
    int subset[n]; // Temporary array to store the current subset
    findSubsets(set, n, sum, subset, 0, 0, 0);
}

int main() {
    int set[] = {10, 7, 5, 18, 12, 20, 15};
    int n = sizeof(set) / sizeof(set[0]);
    int sum = 35;

    printf("Subsets with sum %d are:\n", sum);
    findSubsetsWithSum(set, n, sum);

    return 0;
}

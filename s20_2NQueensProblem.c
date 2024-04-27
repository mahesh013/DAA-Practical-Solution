#include <stdio.h>
#include <stdbool.h>

#define N 4 // Number of queens

// Function to print the board configuration
void printSolution(int board[N][N]) {
    printf("Board Configuration:\n");
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            printf("%c ", board[i][j] ? 'Q' : '.');
        }
        printf("\n");
    }
}

// Function to check if it's safe to place a queen at board[row][col]
bool isSafe(int board[N][N], int row, int col) {
    // Check if there's a queen in the same column
    for (int i = 0; i < row; i++)
        if (board[i][col])
            return false;

    // Check if there's a queen in the upper left diagonal
    for (int i = row, j = col; i >= 0 && j >= 0; i--, j--)
        if (board[i][j])
            return false;

    // Check if there's a queen in the upper right diagonal
    for (int i = row, j = col; i >= 0 && j < N; i--, j++)
        if (board[i][j])
            return false;

    return true;
}

// Recursive function to solve the N Queens Problem
bool solveNQueensUtil(int board[N][N], int row) {
    // Base case: If all queens are placed
    if (row >= N)
        return true;

    // Try placing a queen in each column of the current row
    for (int col = 0; col < N; col++) {
        // Check if it's safe to place a queen at board[row][col]
        if (isSafe(board, row, col)) {
            // Place the queen at board[row][col]
            board[row][col] = 1;

            // Recur to place the rest of the queens
            if (solveNQueensUtil(board, row + 1))
                return true;

            // If placing a queen at board[row][col] doesn't lead to a solution,
            // backtrack and remove the queen from board[row][col]
            board[row][col] = 0;
        }
    }

    // If no queen can be placed in this row, return false
    return false;
}

// Function to solve the N Queens Problem and print the solution
void solveNQueens() {
    int board[N][N] = { {0, 0, 0, 0},
                        {0, 0, 0, 0},
                        {0, 0, 0, 0},
                        {0, 0, 0, 0} };

    if (solveNQueensUtil(board, 0)) {
        printf("Solution found!\n");
        printSolution(board);
    } else {
        printf("Solution not found!\n");
    }
}

// Main function
int main() {
    solveNQueens();
    return 0;
}

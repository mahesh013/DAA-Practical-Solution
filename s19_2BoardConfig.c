#include <stdio.h>

#define N 4 // Number of queens

// Function to print the board configuration
void printBoard(int board[N][N]) {
    printf("Board Configuration:\n");
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            printf("%c ", board[i][j] ? 'Q' : '.');
        }
        printf("\n");
    }
}

int main() {
    int board[N][N] = { {0, 0, 0, 0},
                        {0, 0, 0, 0},
                        {0, 0, 0, 0},
                        {0, 0, 0, 0} };

    // Place queens on the board
    board[0][1] = 1;
    board[1][3] = 1;
    board[2][0] = 1;
    board[3][2] = 1;

    // Print the board configuration
    printBoard(board);

    return 0;
}

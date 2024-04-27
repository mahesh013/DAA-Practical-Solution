#include <stdio.h>
#include <stdlib.h>

#define N 4 // Size of matrices

// Function to add two matrices
void add(int A[][N], int B[][N], int C[][N]) {
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            C[i][j] = A[i][j] + B[i][j];
}

// Function to subtract two matrices
void subtract(int A[][N], int B[][N], int C[][N]) {
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            C[i][j] = A[i][j] - B[i][j];
}

// Function to multiply two matrices using Strassen's algorithm
void strassen(int A[][N], int B[][N], int C[][N]) {
    if (N == 1) {
        C[0][0] = A[0][0] * B[0][0];
        return;
    }

    int A11[N/2][N/2], A12[N/2][N/2], A21[N/2][N/2], A22[N/2][N/2];
    int B11[N/2][N/2], B12[N/2][N/2], B21[N/2][N/2], B22[N/2][N/2];
    int C11[N/2][N/2], C12[N/2][N/2], C21[N/2][N/2], C22[N/2][N/2];
    int P1[N/2][N/2], P2[N/2][N/2], P3[N/2][N/2], P4[N/2][N/2], P5[N/2][N/2], P6[N/2][N/2], P7[N/2][N/2];
    int temp1[N/2][N/2], temp2[N/2][N/2];

    // Dividing the matrices into sub-matrices
    for (int i = 0; i < N/2; i++) {
        for (int j = 0; j < N/2; j++) {
            A11[i][j] = A[i][j];
            A12[i][j] = A[i][j + N/2];
            A21[i][j] = A[i + N/2][j];
            A22[i][j] = A[i + N/2][j + N/2];

            B11[i][j] = B[i][j];
            B12[i][j] = B[i][j + N/2];
            B21[i][j] = B[i + N/2][j];
            B22[i][j] = B[i + N/2][j + N/2];
        }
    }

    // Calculating P1 to P7
    add(A11, A22, temp1);
    add(B11, B22, temp2);
    strassen(temp1, temp2, P1);

    add(A21, A22, temp1);
    strassen(temp1, B11, P2);

    subtract(B12, B22, temp2);
    strassen(A11, temp2, P3);

    subtract(B21, B11, temp2);
    strassen(A22, temp2, P4);

    add(A11, A12, temp1);
    strassen(temp1, B22, P5);

    subtract(A21, A11, temp1);
    add(B11, B12, temp2);
    strassen(temp1, temp2, P6);

    subtract(A12, A22, temp1);
    add(B21, B22, temp2);
    strassen(temp1, temp2, P7);

    // Calculating C matrices
    add(P1, P4, temp1);
    subtract(temp1, P5, temp2);
    add(temp2, P7, C11);

    add(P3, P5, C12);

    add(P2, P4, C21);

    add(P1, P3, temp1);
    subtract(temp1, P2, temp2);
    add(temp2, P6, C22);

    // Combining C matrices into one result matrix
    for (int i = 0; i < N/2; i++) {
        for (int j = 0; j < N/2; j++) {
            C[i][j] = C11[i][j];
            C[i][j + N/2] = C12[i][j];
            C[i + N/2][j] = C21[i][j];
            C[i + N/2][j + N/2] = C22[i][j];
        }
    }
}

// Function to print a matrix
void printMatrix(int A[][N]) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            printf("%d ", A[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

int main() {
    int A[N][N] = {{1, 2, 3, 4},
                   {5, 6, 7, 8},
                   {9, 10, 11, 12},
                   {13, 14, 15, 16}};

    int B[N][N] = {{17, 18, 19, 20},
                   {21, 22, 23, 24},
                   {25, 26, 27, 28},
                   {29, 30, 31, 32}};

    int C[N][N]; // To store the result

    printf("Matrix A:\n");
    printMatrix(A);

    printf("Matrix B:\n");
    printMatrix(B);

    strassen(A, B, C);

    printf("Resultant matrix C:\n");
    printMatrix(C);

    return 0;
}

#include "stdio.h"

int N = 12;
int count = 0;

void printBoard(int board[N][N]) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (board[i][j] == 1) {
                printf("X ");
            } else {
                printf("- ");
            }
        }
        printf("\n");
    }
    printf("\n");
}


int isSafe(int board[N][N], int row, int col) {
    for (int i = 0; i < N; i++) {
        if (board[i][col] == 1) {
            return 0;
        }
    }
    int i = row;
    int j = col;
    while (i >= 0 && j >= 0) {
        if (board[i][j] == 1) {
            return 0;
        }
        i--;
        j--;
    }
    i = row;
    j = col;
    while (i >= 0 && j < N) {
        if (board[i][j] == 1) {
            return 0;
        }
        i--;
        j++;
    }
    return 1;
}

void solveNQueens(int board[N][N], int row) {
    if (row == N) {
        printBoard(board);
        count++;
        return;
    }
    for (int i = 0; i < N; i++) {
        if (isSafe(board, row, i) == 1) {
            board[row][i] = 1;
            solveNQueens(board, row + 1);
            board[row][i] = 0;
        }
    }
}

int main() {
    int board[N][N];
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            board[i][j] = 0;
        }
    }
    solveNQueens(board, 0);
    printf("Counter: %d", count);
    return 0;
}
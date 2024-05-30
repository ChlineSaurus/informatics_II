#include "stdio.h"

int N = 15;
int count = 0;

void printBoard(int board[N]) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (board[i] == j) {
                printf("X ");
            } else {
                printf("- ");
            }
        }
        printf("\n");
    }

    for (int i = 0; i < N; i++) {
        printf("%d, ", board[i]);
    }
    printf("\n\n");
}


int isSafe(int board[N], int row, int col) {
    int down = col;
    int up = col;
    for (int i = row; i >= 0; i--) {
        if (down == board[i]) {
            return 0;
        }
        if (up == board[i]) {
            return 0;
        }
        down--;
        up++;
    }
    return 1;
}

void solveNQueens(int board[N], int available[N], int row) {
    if (row == N) {
        //printBoard(board);
        count++;
        return;
    }
    for (int i = 0; i < N; i++) {
        if (available[i] == 1) {
            if (isSafe(board, row, i)) {
                board[row] = i;
                available[i] = 0;
                solveNQueens(board, available, row + 1);
                board[row] = -1;
                available[i] = 1;
            }
        }
    }
}

int main() {
    int board[N];
    int available[N];
    for (int i = 0; i < N; i++) {
        available[i] = 1;
        board[i] = -1;
    }
    solveNQueens(board, available, 0);
    printf("Counter: %d", count);
    return 0;
}
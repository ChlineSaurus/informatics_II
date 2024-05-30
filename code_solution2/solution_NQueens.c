#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int N = 12;
int count = 0;

void printBoard(int board[N][N]) {
    printf("Solution %d:\n", count);
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            printf("%c ", board[i][j] ? 'Q' : '.');
        }
        printf("\n");
    }
    printf("\n");
}

/**
 * Check if it's safe to place a new Queen in the given position
*/
int isSafe(int board[N][N], int row, int col) {
    // check column
    for (int i = 0; i < row; i++) {
        if (board[i][col]) {
            return 0;
        }
    }
    // check diag
    for (int i = row, j = col; i >= 0 && j >= 0; i--, j--) {
        if (board[i][j]) {
            return 0;
        }
    }
    // check inv-diag
    for (int i = row, j = col; i >= 0 && j < N; i--, j++) {
        if (board[i][j]) {
            return 0;
        }
    }
    return 1;
}


/**
 * Try to place N queens in the board 
 * and update the global variable 'count'
*/
void solveNQueens(int board[N][N], int row) {
    if (row == N) {
        count++;
        // printBoard(board);
        return;
    }

    for (int col = 0; col < N; col++) {
        if (isSafe(board, row, col) == 1) {
            board[row][col] = 1;
            // go to next row
            solveNQueens(board, row + 1);
            // reverse 
            board[row][col] = 0;
        }
    }
}

int main() {
    int board[N][N];
    memset(board, 0, sizeof(board));

    // try to place Queen row by row
    solveNQueens(board, 0);

    printf("Total solutions: %d\n", count);

    return 0;
}
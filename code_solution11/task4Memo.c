#include <stdio.h>
#include <stdlib.h>

#define N 5
int memo[N][N];
int a[N] = {3, 2, 4, 1};

int max(int a, int b) { return a>b ? a : b; }

/**
   i: left start index
   j: right end index
   k: iteration
 **/

int memoMaxCost(int i, int j, int k) {
    // return memorized value if it already is computed
    if (memo[i][j] != -1) {
        return memo[i][j];
    }

    // no more elements we can delete (base case)
    if (i > j) {
        return 0;
    }

    memo[i][j] = max(memoMaxCost(i+1, j, k+1) + k*a[i],
                     memoMaxCost(i, j-1, k+1) + k*a[j]);
    return memo[i][j];
}

int main() {

    /* init memo matrix */
    for (int i=0; i < N; ++i) {
        for (int j=0; j < N; ++j) {
            memo[i][j] = -1;
        }
    }

    printf("%d", memoMaxCost(0, N-1, 0));
    return 0;
}
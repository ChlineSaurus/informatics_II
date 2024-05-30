
#include "stdio.h"

long fibonacciRecursive(long n, long *totalCalls) {
    (*totalCalls)++;
    if (n <= 1) {
        return n;
    }
    return fibonacciRecursive(n - 1, totalCalls) + fibonacciRecursive(n - 2, totalCalls);
}

long fibonacciIterative(long n, long *totalIterations) {
    int a = 0, b = 1, c, i;
    if (n == 0){
        return 0;
    }
    for (i = 2; i <= n; i++) {
        c = a + b; // Calculate the next number in the sequence
        a = b;     // Move a and b one step forward in the sequence
        b = c;
        (*totalIterations)++; // Increment the total iterations count
    }
    // For n > 0, we start counting from 2, so initialize totalIterations with 1 to account for the first step
    *totalIterations = 1 + *totalIterations;

    return b; // b is the nth Fibonacci number at this point

}

int main() {
    long totalCalls = 0;
    long n = 40;
    printf("Fibonacci Recursive: %ld, Total calls: %ld\n", fibonacciRecursive(n, &totalCalls), totalCalls);
    int totalIterations = 0;
    printf("Fibonacci Iterative: %ld, Total iterations: %d\n", fibonacciIterative(n, &totalIterations), totalIterations);
}
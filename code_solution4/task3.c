#include <stdio.h>

int findMajority(int A[], int left, int right) {
    if (left == right) {
        return A[left];
    }
    int mid = (left + right) / 2;
    int leftMajority = findMajority(A, left, mid);
    int rightMajority = findMajority(A, mid + 1, right);
    if (leftMajority == rightMajority) {
        return leftMajority;
    }
    int countLeft = 0;
    int countRight = 0;
    for (int i = left; i <= right; i++) {
        if (A[i] == leftMajority) {
            countLeft += 1;
        } else if (A[i] == rightMajority) {
            countRight += 1;
        }
    }
    if (countLeft >= countRight) {
        return leftMajority;
    }
    return rightMajority;
}

void printArray(int A[], int n) {
    for (int i = 0; i < n - 1; i++) {
        printf("%d, ", A[i]);
    }
    printf("%d", A[n - 1]);
}

int main() {
    int A[] = {1, 2, 6, 2, 1, 2, 1, 1, 1};
    int n = sizeof(A)/sizeof(A[0]);

    int majority_element = findMajority(A, 0, n - 1);

    printf("The majority element of the array A = [");
    printArray(A, n);
    printf("] is %d.", majority_element);
    return 0;
}
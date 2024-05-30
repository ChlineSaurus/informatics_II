#include "stdio.h"

int isPalindrome(char X[], int i, int j) {
    if(i >= j) {
        return 1;
    } else if (X[i] != X[j]) {
        return 0;
    }
    return isPalindrome(X, ++i, --j);
}

int main() {
    char aString[] = "1a b3cD45t54Dc3b a1";
    int length = sizeof(aString);
    printf("%d", isPalindrome(aString, 0, length - 2));
    return 0;
}
#include <stdio.h>

#define isEmpty (-1)
#define true 1
#define false 0
#define stackSize 100

int S[stackSize];
int topIndex = 0;

void new() {
    topIndex = 0;
    printf("The stack has been reset. \n");
}

int is_empty() {
    if (topIndex == 0) {
        return true;
    }
    return false;
}

int pop() {
    if (is_empty() == true) {
        return isEmpty;
    }
    return S[--topIndex];
}

void push(int x) {
    if (topIndex + 1 == stackSize) {
        printf("Stack is already full. \n");
        return;
    }
    S[topIndex++] = x;
}

void print_stack() {
    printf("Stack: ");
    for (int i = 0; i < topIndex; i++) {
        printf("%d, ", S[i]);
    }
    printf("\n");
}

int main() {
    new();
    for (int i = 0; i < 10; i++) {
        push(i);
    }
    print_stack();
    printf("Pop stack: ");
    for (int i = 0; i < 10; i++) {
        printf("%d, ", pop());
    }
    printf("\n");
    printf("isEmpty: %d\n", is_empty());
    push(1);
    printf("isEmpty: %d\n", is_empty());
    return 0;
}
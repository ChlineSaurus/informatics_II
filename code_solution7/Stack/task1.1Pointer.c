#include <stdio.h>
#include <stdlib.h>

#define isEmpty (-1)
#define true 1
#define false 0
#define stackSize 100

struct node {
    int value;
    struct node *next;
};

struct node *S = NULL;
int currentAmount = 0;

void new() {
    struct node *temp;
    while (S != NULL) {
        temp = S;
        S = S->next;
        free(temp);
    }
    currentAmount = 0;
    printf("The stack has been reset. \n");
}

int is_empty() {
    if (S == NULL) {
        return true;
    }
    return false;
}

int pop() {
    if (is_empty() == true) {
        return isEmpty;
    }
    struct node *temp = S;
    int value = S->value;
    S = S->next;
    free(temp);
    return value;
}

void push(int x) {
    struct node *newNode = malloc(sizeof(struct node));
    newNode->next = S;
    newNode->value = x;
    S = newNode;
}

void print_stack_recursive(struct node *runner) {
    if (runner != NULL) {
        print_stack_recursive(runner->next);
        printf("%d, ", runner->value);
    }
}

void print_stack() {
    printf("Stack: ");
    print_stack_recursive(S);
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
    print_stack();
    new();
    print_stack();
    return 0;
}
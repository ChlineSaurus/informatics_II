#include <stdio.h>
#include <stdlib.h>

#define isEmpty (-1)
#define true 1
#define false 0

struct node {
    int value;
    struct node *next;
};

struct node** new() {
    struct node **newStack = malloc(sizeof(struct node*));
    printf("The stack has been reset. \n");
    return newStack;
}

int is_empty(struct node **S) {
    if (*S == NULL) {
        return true;
    }
    return false;
}

int pop(struct node **S) {
    if (is_empty(S) == true) {
        return isEmpty;
    }
    struct node *temp = *S;
    int value = (*S)->value;
    *S = (*S)->next;
    free(temp);
    return value;
}

void push(struct node **S, int x) {
    struct node *newNode = malloc(sizeof(struct node));
    newNode->next = *S;
    newNode->value = x;
    *S = newNode;
}

void print_stack_recursive(struct node *runner) {
    if (runner != NULL) {
        print_stack_recursive(runner->next);
        printf("%d, ", runner->value);
    }
}

void print_stack(struct node **S) {
    printf("Stack: ");
    print_stack_recursive(*S);
    printf("\n");
}

int main() {
    struct node **S1 = new();
    struct node **S2 = new();
    for (int i = 0; i < 10; i++) {
        push(S1, i);
        push(S2, i*10);
    }
    print_stack(S1);
    print_stack(S2);
    printf("Pop stack: ");
    for (int i = 0; i < 10; i++) {
        printf("%d, ", pop(S1));
    }
    printf("\n");
    printf("isEmpty: %d\n", is_empty(S1));
    pop(S1);
    push(S1, 1);
    printf("isEmpty: %d\n", is_empty(S1));
    return 0;
}
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

struct node** new() {
    struct node **newStack = malloc(sizeof(struct node));
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
        printf("Stack is already full. \n");
        return isEmpty;
    }
    struct node *temp = *S;
    int value = (*S)->value;
    *S = (*S)->next;
    free(temp);
    return value;
}

int peek(struct node **S) {
    if (is_empty(S) == true) {
        printf("Stack is already full. \n");
        return isEmpty;
    }
    return (*S)->value;
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

void stackSort(struct node **S) {
    struct node **supply = new();
    struct node **auxiliaryStack = new();
    while (is_empty(S) == false) {
        push(supply, pop(S));
    }
    int currentElement;
    while (is_empty(supply) == false) {
        currentElement = pop(supply);
        while(is_empty(S) == false) {
            if(peek(S) < currentElement) {
                push(auxiliaryStack, pop(S));
            } else {
                break;
            }
        }
        push(S, currentElement);
        while (is_empty(auxiliaryStack) == false) {
            push(S, pop(auxiliaryStack));
        }
    }
}

int main() {
    int array[] = {11, 14,1,12,5,6,9,2,7,
                   3,8,13, 0, 4, 10};
    int length = sizeof(array) /sizeof(array[0]);
    struct node **originalStack = new();
    for(int i = 0; i < length; i++) {
        push(originalStack, array[i]);
    }
    stackSort(originalStack);
}
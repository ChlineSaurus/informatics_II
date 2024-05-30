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

void delete_stack(struct node **S) {
    struct node *temp;
    while (*S != NULL) {
        temp = *S;
        *S = (*S)->next;
        free(temp);
    }
}

void stackSort(struct node **S) {
    struct node **smaller = new();
    struct node **biggerEqual = new();
    int pivot;
    if(is_empty(S) == false) {
        pivot = pop(S);
    } else {
        return;
    }
    int topElement;
    while (is_empty(S) == false) {
        topElement = pop(S);
        if(topElement >= pivot) {
            push(biggerEqual, topElement);
        } else {
            push(smaller, topElement);
        }
    }
    stackSort(biggerEqual);
    stackSort(smaller);

    struct node **auxiliary = new();
    while (is_empty(smaller) == false) {
        push(auxiliary, pop(smaller));
    }
    while (is_empty(auxiliary) == false) {
        push(S, pop(auxiliary));
    }
    push(S,pivot);
    while (is_empty(biggerEqual) == false) {
        push(auxiliary, pop(biggerEqual));
    }
    while (is_empty(auxiliary) == false) {
        push(S, pop(auxiliary));
    }
    delete_stack(smaller);
    delete_stack(auxiliary);
    delete_stack(biggerEqual);
}

int main() {
    int array[] = {11, 14,1,20,16, 12,5,6,9,2,7, 18,
                   3,8,17, 5,13, 0, 4, 10, 15, 19};
    int length = sizeof(array) /sizeof(array[0]);
    struct node **originalStack = new();
    for(int i = 0; i < length; i++) {
        push(originalStack, array[i]);
    }
    stackSort(originalStack);
    print_stack(originalStack);
}
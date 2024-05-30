#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define isEmpty (-1)
#define true 1
#define false 0

struct node {
    int value;
    struct node *next;
};

struct node *head;
struct node *tail;

void new() {
    struct node *temp;
    while (head != NULL) {
        temp = head;
        head = head->next;
        free(temp);
    }
    tail = NULL;
    printf("The queue has been reset. \n");
}

bool is_empty() {
    if (head == NULL) {
        return true;
    }
    return false;
}

void enqueue(int x) {
    struct node *newNode = malloc(sizeof(struct node));
    newNode->value = x;
    newNode->next = NULL;
    if (is_empty() == true) {
        head = newNode;
        tail = newNode;
        return;
    }
    tail->next = newNode;
    tail = newNode;
}

int dequeue() {
    if (is_empty() == true) {
        return isEmpty;
    }
    int value = head->value;
    struct node *temp = head;
    head = head->next;
    free(temp);
    return value;
}

void print_queue() {
    printf("Queue: ");
    struct node *runner = head;
    while (runner != NULL) {
        printf("%d, ", runner->value);
        runner = runner->next;
    }
    printf("\n");
}

int main() {
    new();
    for (int i = 0; i < 10; i++) {
        enqueue(i);
    }
    print_queue();
    printf("Dequeue: ");
    for (int i = 0; i < 10; i++) {
        printf("%d, ", dequeue());
    }
    printf("\n");
    printf("isEmpty: %d\n", is_empty());
    printf("Not possible dequeue: %d \n", dequeue());
    enqueue(1);
    printf("isEmpty: %d\n", is_empty());
    new();
    return 0;
}
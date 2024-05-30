#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define isEmpty (-1)
#define true 1
#define false 0

struct queue {
    struct node *head;
    struct node *tail;
    int maxLength;
    int currentLength;
};

struct node {
    int value;
    struct node *next;
};

struct queue *new(int maxLength) {
    struct queue *newQueue = malloc(sizeof(struct queue));
    newQueue->head = NULL;
    newQueue->tail = NULL;
    newQueue->currentLength = 0;
    newQueue->maxLength = maxLength;
    return newQueue;
}

bool is_empty(struct queue *Q) {
    if (Q->head == NULL) {
        return true;
    }
    return false;
}

void enqueue(struct queue *Q, int x) {
    struct node *newNode = malloc(sizeof(struct node));
    newNode->value = x;
    newNode->next = NULL;
    if (is_empty(Q) == true) {
        Q->head = newNode;
        Q->tail = newNode;
        return;
    }
    Q->tail->next = newNode;
    Q->tail = newNode;
}

int dequeue(struct queue *Q) {
    if (is_empty(Q) == true) {
        return isEmpty;
    }
    int value = Q->head->value;
    struct node *temp = Q->head;
    Q->head = Q->head->next;
    free(temp);
    Q->currentLength--;
    return value;
}

void print_queue(struct queue *Q) {
    printf("Queue: ");
    struct node *runner = Q->head;
    while (runner != NULL) {
        printf("%d, ", runner->value);
        runner = runner->next;
    }
    printf("\n");
}

int main() {
    struct queue *Q1 = new(100);
    struct queue *Q2 = new(1000);
    for (int i = 0; i < 10; i++) {
        enqueue(Q1, i);
        enqueue(Q2, i * 10);
    }
    print_queue(Q1);
    print_queue(Q2);
    printf("Dequeue: ");
    for (int i = 0; i < 10; i++) {
        printf("%d, ", dequeue(Q1));
    }
    printf("\n");
    printf("isEmpty: %d\n", is_empty(Q1));
    dequeue(Q1);
    enqueue(Q1, 1);
    printf("isEmpty: %d\n", is_empty(Q1));

    return 0;
}
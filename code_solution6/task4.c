#include <stdio.h>
#include <stdlib.h>

struct node {
    int value;
    struct node *next;
    struct node *prev;
};

struct node* createDoublyLinkedList(int array[], int length) {
    struct node *node_array[length];
    for(int i = 0; i < length; i++) {
        node_array[i] = malloc(sizeof(struct node));
        node_array[i]->value = array[i];
    }
    for(int i = 0; i < length - 1; i++) {
        node_array[i]->next = node_array[i+1];
    }
    node_array[length-1]->next = NULL;
    for(int i = length-1; i > 0; i--) {
        node_array[i]->prev = node_array[i-1];
    }
    node_array[0]->prev = NULL;
    return node_array[0];
}

void printLinkedList(struct node *head) {
    while (head != NULL) {
        printf("%d, ", head->value);
        head = head->next;
    }
    printf("\n");
}

struct node* reverseLinkedList(struct node *head) {
    if (head == NULL) {
        return NULL;
    }

    struct node *walker = NULL;
    struct node *runner = head;

    while (runner != NULL) {
        runner->prev = runner->next;
        runner->next = walker;
        walker = runner;
        runner = runner->prev;
    }
    return walker;
}

struct node* reverseLinkedListRecursive(struct node *head) {
    if (head == NULL) {
        return NULL;
    }

    struct node* temp = head->next;
    head->next = head->prev;
    head->prev = temp;

    if (head->prev == NULL) {
        return head;
    }

    return reverseLinkedListRecursive(head->prev);
}

int main() {
    int array[] = {0,1,1,2,3,5,8,13};
    struct node * headLinkedList = createDoublyLinkedList(array, sizeof(array)/sizeof(array[0]));
    printLinkedList(headLinkedList);
    headLinkedList = reverseLinkedListRecursive(headLinkedList);
    printLinkedList(headLinkedList);
}
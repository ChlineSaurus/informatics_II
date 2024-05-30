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

struct node* mergeLinkedList(struct node *headList1, struct node *headList2) {
    if (headList1 == NULL) {
        return headList2;
    }
    if (headList2 == NULL) {
        return headList1;
    }

    struct node *headMergedLinkedList;
    struct node *walker;
    struct node *runnerList1 = headList1;
    struct node *runnerList2 = headList2;

    if(runnerList1->value <= runnerList2->value) {
        headMergedLinkedList = runnerList1;
        walker = runnerList1;
        runnerList1 = runnerList1->next;
    } else {
        headMergedLinkedList = runnerList2;
        walker = runnerList2;
        runnerList1 = runnerList2->next;
    }

    while (runnerList1 != NULL && runnerList2 != NULL) {
        if(runnerList1->value <= runnerList2->value) {
            walker->next = runnerList1;
            runnerList1->prev = walker;
            runnerList1 = runnerList1->next;
        } else {
            walker->next = runnerList2;
            runnerList2->prev = walker;
            runnerList2 = runnerList2->next;
        }
        walker = walker->next;
    }

    if(runnerList1 != NULL) {
        walker->next = runnerList1;
        runnerList1->prev = walker;
    } else {
        walker->next = runnerList2;
        runnerList2->prev = walker;
    }
    return headMergedLinkedList;
}

int main() {
    int list1[] = {1, 3, 5, 7, 9, 12, 15, 18};
    int list2[] = {2, 4, 6, 8, 10, 11, 19, 22};
    struct node *headList1 = createDoublyLinkedList(list1, sizeof(list1) / sizeof(list1[0]));
    struct node *headList2 = createDoublyLinkedList(list2, sizeof(list2) / sizeof(list2[0]));
    printLinkedList(headList1);
    printLinkedList(headList2);
    struct node *mergedLinkedList = mergeLinkedList(headList1, headList2);
    printLinkedList(mergedLinkedList);
    return 0;
}
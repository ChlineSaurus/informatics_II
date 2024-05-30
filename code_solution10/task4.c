#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define notFound (-1)
#define true 1
#define false 0

struct node {
    int value;
    struct node *next;
};

int hash(struct node *key, int length) {
    return (intptr_t) key * 97 % length;
}

void printHT(struct node *hashTable[], int length) {
    printf("Hash Table: ");
    for (int i = 0; i < length; ++i) {
        printf("%d, ", hashTable[i]);
    }
    printf("\n");
}

int insertKey(struct node *hashTable[], struct node *insertNode, int length) {
    int collision = 0;
    int currentIndex = hash(insertNode, length);

    while (collision < length) {
        if (hashTable[currentIndex] != NULL) {
            collision++;
            currentIndex = (currentIndex + 1) % length;
        } else {
            hashTable[currentIndex] = insertNode;
            break;
        }
    }

    if (collision == length) {
        return false;
    }

    return true;
}

void initHashTable( struct node *hashTable[], int length) {
    for (int i = 0; i < length; ++i) {
        hashTable[i] = NULL;
    }
}

int getKeyIndex(struct node *hashTable[], struct node *searchNode, int length) {
    int currentIndex = hash(searchNode, length);
    int collisions = 0;

    while (hashTable[currentIndex] != NULL && collisions < length) {
        if (hashTable[currentIndex] == searchNode) {
            return currentIndex;
        }
        currentIndex = (currentIndex + 1) % length;
    }
    return notFound;
}

struct node *createLinkedList(int *array, int length) {
    if (length == 0) {
        return NULL;
    }
    struct node *root = malloc(sizeof(struct node));
    root->value = array[0];
    struct node *runner = root;
    for (int i = 1; i < length; i++) {
        runner->next = malloc(sizeof(struct node));
        runner = runner->next;
        runner->value = array[i];
    }
    return root;
}

int detectCycle(struct node *head) {
    int length = 100;
    struct node *hashTable[length];
    initHashTable(hashTable, length);
    struct node *currentNode = head;

    while(currentNode != NULL) {
        if(getKeyIndex(hashTable, currentNode, length) != notFound) {
            return true;
        }
        insertKey(hashTable, currentNode, length);
        currentNode = currentNode->next;
    }
    return false;
}

int detectCycle2(struct node *head) {
    struct node *walker = head;
    struct node *runner = head;

    while(1) {
        if(runner == NULL || runner->next == NULL) {
            return false;
        }
        walker = walker->next;
        runner = runner->next->next;
        if(walker == runner) {
            return true;
        }
    }
}

int main(int argc, char *argv[]) {
    int array[] = {1, 2, 3, 4, 5, 6, 7};
    int length = sizeof(array) / sizeof(array[0]);


    struct node *rootLinkedList1 = createLinkedList(array, length);
    struct node *runner = rootLinkedList1;
    while (runner->next != NULL) {
        runner = runner->next;
    }
    runner->next = rootLinkedList1;
    printf("Linked list 1: %d \n", detectCycle(rootLinkedList1));


    struct node *rootLinkedList2 = createLinkedList(array, length);
    runner = rootLinkedList2;
    while (runner->next != NULL) {
        runner = runner->next;
    }
    runner->next = runner;
    printf("Linked list 2: %d \n", detectCycle(rootLinkedList2));


    struct node *rootLinkedList3 = createLinkedList(array, length);
    printf("Linked list 3: %d \n", detectCycle(rootLinkedList3));


    return 0;
}

#include <stdio.h>
#include <stdbool.h>

#define isEmpty (-1)
#define true 1
#define false 0
#define queueSize 100

int head = 0;
int tail = 0;

int Q[queueSize];

void new() {
    head = 0;
    tail = 0;
    printf("The queue has been reset. \n");
}

bool is_empty() {
    if (head == tail) {
        return true;
    }
    return false;
}

void enqueue(int x) {
    if ((tail + 1) % queueSize == head) {
        printf("Queue is already full. \n");
        return;
    }
    Q[tail] = x;
    tail = (tail + 1) % queueSize;
}

int dequeue() {
    if(is_empty() == true) {
        return isEmpty;
    }
    int value = Q[head];
    head = (head + 1) % queueSize;
    return value;
}

void print_queue() {
    printf("Queue: ");
    int i = head;
    while (i != tail) {
        printf("%d, ", Q[i]);
        i = (i + 1) % queueSize;
    }
    printf("\n");
}

void generate(int n) {
    new();
    enqueue(1);
    int i = 0;
    int currentValue;
    printf("Sequence: ");
    while (i < n) {
        currentValue = dequeue();
        printf("%d, ", currentValue);
        enqueue(currentValue * 3 + 1);
        enqueue(currentValue * 3 + 2);
        i++;
    }
    printf("\n");
}

int main() {
    generate(30);
    return 0;
}
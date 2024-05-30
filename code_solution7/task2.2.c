#include <stdio.h>
#include <stdlib.h>

#define isEmpty (-1)
#define true 1
#define false 0
#define stackSize 100

struct node {
    char value;
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
}

int is_empty() {
    if (S == NULL) {
        return true;
    }
    return false;
}

char pop() {
    if (is_empty() == true) {
        printf("Stack is already full. \n");
        return isEmpty;
    }
    struct node *temp = S;
    char value = S->value;
    S = S->next;
    free(temp);
    currentAmount--;
    return value;
}

void push(char x) {
    if (currentAmount > stackSize) {
        printf("Stack is already full. \n");
        return;
    }
    struct node *newNode = malloc(sizeof(struct node));
    newNode->next = S;
    newNode->value = x;
    S = newNode;
    currentAmount++;
}

void printStackRecursive(struct node *runner) {
    if (runner != NULL) {
        printStackRecursive(runner->next);
        printf("%c, ", runner->value);
    }
}

void printStack() {
    printf("Stack: ");
    printStackRecursive(S);
    printf("\n");
}

int checkParenthesis(char string[]) {
    new();
    int i = 0;
    char currentElement;
    while (string[i] != '\0') {
        currentElement = string[i];
        if(currentElement == '(' || currentElement == '[') {
            push(currentElement);
        } else if (currentElement == ')' || currentElement == ']') {
            if (is_empty() == true) {
                return false;
            } else {
                char topOfStack = pop();
                if(currentElement == ')') {
                    if(topOfStack != '(') {
                        return false;
                    }
                } else if (topOfStack != '['){
                    return false;
                }
            }
        } else {
            continue;
        }
        i++;
    }
    if(is_empty() == true) {
        return true;
    }
    return false;
}

int main() {
    char *example1 = "((())";
    char *example2 = "([(]))";
    char *example3 = "][";
    checkParenthesis(example1);
    checkParenthesis(example2);
    checkParenthesis(example3);
    char *correct1 = "(())", *correct2 = "[()][]()", *correct3 = "[[()[()]]]";
    char *wrong1 = "(()", *wrong2 = "[[()]", *wrong3 = "[(])";
    printf("String: %s, Result: %d\n", correct1, checkParenthesis(correct1));
    printf("String: %s, Result: %d\n", correct2, checkParenthesis(correct2));
    printf("String: %s, Result: %d\n", correct3, checkParenthesis(correct3));
    printf("String: %s, Result: %d\n", wrong1, checkParenthesis(wrong1));
    printf("String: %s, Result: %d\n", wrong2, checkParenthesis(wrong2));
    printf("String: %s, Result: %d\n", wrong3, checkParenthesis(wrong3));
    return 0;
}

#include "stdio.h"
#include "stdlib.h"

#define true 1
#define false 0

struct TreeNode {
    int val;
    int level;
    struct TreeNode *left;
    struct TreeNode *right;
};

struct node {
    struct TreeNode *value;
    struct node *next;
};

struct node **new() {
    struct node **newStack = malloc(sizeof(struct node *));
    return newStack;
}

int is_empty(struct node **S) {
    if (*S == NULL) {
        return true;
    }
    return false;
}

struct TreeNode *pop(struct node **S) {
    if (is_empty(S) == true) {
        return NULL;
    }
    struct node *temp = *S;
    struct TreeNode *value = (*S)->value;
    *S = (*S)->next;
    free(temp);
    return value;
}

void push(struct node **S, struct TreeNode *x) {
    struct node *newNode = malloc(sizeof(struct node));
    newNode->next = *S;
    newNode->value = x;
    *S = newNode;
}

void insert(struct TreeNode **root, int val) {
    struct TreeNode *newNode = malloc(sizeof(struct TreeNode));
    newNode->val = val;
    newNode->left = NULL;
    newNode->right = NULL;

    if (*root == NULL) {
        *root = newNode;
        return;
    }
    struct TreeNode *walker = NULL;
    struct TreeNode *runner = *root;

    while (runner != NULL) {
        walker = runner;
        if (runner->val >= val) {
            runner = runner->left;
        } else {
            runner = runner->right;
        }
    }

    if (walker->val >= val) {
        walker->left = newNode;
    } else {
        walker->right = newNode;
    }
}

void delete(struct TreeNode **root, int val) {
    struct TreeNode *walker = NULL;
    struct TreeNode *runner = *root;

    while (runner != NULL && runner->val != val) {
        walker = runner;
        if (runner->val >= val) {
            runner = runner->left;
        } else {
            runner = runner->right;
        }
    }

    if (runner == NULL) {
        printf("The value you tried to delete didn't exist\n");
        return;
    }

    int children = 0;
    if (runner->left != NULL) {
        children++;
    }
    if (runner->right != NULL) {
        children++;
    }

    if (children == 0) {
        if (*root == runner) {
            *root = NULL;
        } else if (walker->left == runner) {
            walker->left = NULL;
        } else /* walker->right == runner */ {
            walker->right = NULL;
        }
    } else if (children == 1) {
        if (runner->left == NULL) {
            if (*root == runner) {
                *root = runner->right;
            } else if (walker->left == runner) {
                walker->left = runner->right;
            } else /* walker->right == runner */ {
                walker->right = runner->right;
            }
        } else /* runner->right == NULL */ {
            if (*root == runner) {
                *root = runner->left;
            } else if (walker->left == runner) {
                walker->left = runner->left;
            } else /* walker->right == runner */ {
                walker->right = runner->left;
            }
        }
    } else /* children == 2 */ {
        struct TreeNode *runnerPredecessor = runner->left;
        struct TreeNode *walkerPredecessor = runner->left;

        while (runnerPredecessor->right != NULL) {
            walkerPredecessor = runnerPredecessor;
            runnerPredecessor = runnerPredecessor->right;
        }

        if (*root == runner) {
            *root = runnerPredecessor;
        } else if (walker->left == runner) {
            walker->left = runnerPredecessor;
        } else /* walker->right == runner */ {
            walker->right = runnerPredecessor;
        }
        runnerPredecessor->right = runner->right;
        if (runnerPredecessor != walkerPredecessor) {
            walkerPredecessor->right = runnerPredecessor->left;
            runnerPredecessor->left = runner->left;
        }
    }
    free(runner);
}

void printTree(struct TreeNode *currentNode, int level) {
    if (currentNode == NULL) {
        return;
    }
    if (level == 0) {
        printf("Print tree: \n");
        printf("Root -- %d : 0 \n", currentNode->val);
    }
    if (currentNode->left != NULL) {
        printf(" %d -- %d : %d\n", currentNode->val, currentNode->left->val, level + 1);
        printTree(currentNode->left, level + 1);
    }
    if (currentNode->right != NULL) {
        printf(" %d -- %d : %d\n", currentNode->val, currentNode->right->val, level + 1);
        printTree(currentNode->right, level + 1);
    }
}

void visitNode(struct TreeNode *currentNode) {
    printf("%d, ", currentNode->val);
}


void traverseTreeIn(struct TreeNode *currentNode) {
    if (currentNode->left != NULL) {
        traverseTreeIn(currentNode->left);
    }
    visitNode(currentNode);
    if (currentNode->right != NULL) {
        traverseTreeIn(currentNode->right);
    }
}

struct TreeNode *peek(struct node **S) {
    if (is_empty(S) == true) {
        printf("Stack is already full. \n");
        return NULL;
    }
    return (*S)->value;
}

struct TreeNode **createTree(int array[], int length) {
    struct TreeNode **root = malloc(sizeof(struct TreeNode *));
    for (int i = 0; i < length; i++) {
        insert(root, array[i]);
    }
    return root;
}

int maximum(int array[], int length) {
    if (length <= 0) {
        return 0;
    }
    int max = array[0];
    for (int i = 1; i < length; i++) {
        if (array[i] > max) {
            max = array[i];
        }
    }
    return max;
}

int calculateHeight(struct TreeNode *currentNode) {
    if (currentNode == NULL) {
        return 0;
    }
    int possibleValues[] = {calculateHeight(currentNode->left),
                            calculateHeight(currentNode->right)};
    return maximum(possibleValues, 2) + 1;
}

void stackSort(struct node **S) {
    struct node **supply = new();
    struct node **auxiliaryStack = new();
    while (is_empty(S) == false) {
        push(supply, pop(S));
    }
    struct TreeNode *currentElement;
    while (is_empty(supply) == false) {
        currentElement = pop(supply);
        while (is_empty(S) == false) {
            if (peek(S)->level < currentElement->level) {
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

void allNodesToStack(struct node **stack, struct TreeNode *currentNode, int level) {
    if (currentNode == NULL) {
        return;
    }
    currentNode->level = level;
    push(stack, currentNode);
    allNodesToStack(stack, currentNode->right, level + 1);
    allNodesToStack(stack, currentNode->left, level + 1);
}

void traverseTreeSorted(struct TreeNode *root) {
    struct node **result = new();
    allNodesToStack(result, root, 0);
    stackSort(result);

    int level = 0;
    struct TreeNode *currentNode;
    while (is_empty(result) == false) {
        currentNode = pop(result);
        if (currentNode->level != level) {
            level++;
            printf("\n");
        }
        visitNode(currentNode);
    }
}

int diameter(struct TreeNode *currentNode) {

    if (currentNode == NULL) {
        return 0;
    }
    int diameterLeft = diameter(currentNode->left);
    int diameterRight = diameter(currentNode->right);
    int diameterCurrent = calculateHeight(currentNode->left) + calculateHeight(currentNode->right) + 1;
    int possibleValues[] = {diameterLeft, diameterRight, diameterCurrent};
    traverseTreeSorted(currentNode);
    printf("\nCurrent diameter: %d \n\n", maximum(possibleValues, 3));
    return maximum(possibleValues, 3);
}

int main() {
    int array[] = {9, 3, 10, 6, 12, 1, 8};
    struct TreeNode **root = createTree(array, sizeof(array) / sizeof(array[0]));
    traverseTreeIn(*root);
    printf("\n\n");
    diameter(*root);
}
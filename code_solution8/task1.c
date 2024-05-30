#include "stdio.h"
#include "stdlib.h"

struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};

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
        if(runnerPredecessor != walkerPredecessor) {
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

void traverseTreePre(struct TreeNode *currentNode) {
    visitNode(currentNode);
    if (currentNode->left != NULL) {
        traverseTreePre(currentNode->left);
    }
    if (currentNode->right != NULL) {
        traverseTreePre(currentNode->right);
    }
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


void traverseTreePost(struct TreeNode *currentNode) {
    if (currentNode->left != NULL) {
        traverseTreeIn(currentNode->left);
    }
    if (currentNode->right != NULL) {
        traverseTreeIn(currentNode->right);
    }
    visitNode(currentNode);
}

void traverseTree(struct TreeNode **root) {
    printf("Pre order tree traversal: ");
    traverseTreePre(*root);
    printf("\n");

    printf("In order tree traversal: ");
    traverseTreeIn(*root);
    printf("\n");

    printf("Post order tree traversal: ");
    traverseTreePost(*root);
    printf("\n");
}

struct TreeNode **createTree(int array[], int length) {
    struct TreeNode **root = malloc(sizeof(struct TreeNode *));
    for (int i = 0; i < length; i++) {
        insert(root, array[i]);
    }
    return root;
}

int main() {
    int array[] = {9, 3, 10, 6, 12, 1, 8};
    struct TreeNode **root = createTree(array, sizeof(array) / sizeof(array[0]));
    printTree(*root, 0);
    traverseTree(root);
    delete(root, 3);
    printTree(*root, 0);
}
#include <stdio.h>
#include <malloc/_malloc.h>

#define MAX_VERTICES 9
#define INF 1000
#define false 0
#define true 1

struct vertex {
    int predecessor;
    int partOfMST;
    int weight;
    int index;
};

struct linkedListNode {
    int index;
    int weight;
    struct linkedListNode *next;
};

struct heap {
    struct vertex *array[MAX_VERTICES];
    int lastIndex;
};

void createGraph(int lengthEdges, int edges[lengthEdges], int lengthVertices, struct linkedListNode *graph[lengthVertices]) {
    for (int i = 0; i < lengthVertices; i++) {
        graph[i] = NULL;  // Initialize all adjacency lists to NULL
    }

    for (int i = 0; i < lengthEdges; i++) {
        int from = edges[3 * i];
        int to = edges[3 * i + 1];
        int weight = edges[3 * i + 2];

        // Add 'to' to the adjacency list of 'from'
        struct linkedListNode *newNode = malloc(sizeof(struct linkedListNode));
        newNode->index = to;
        newNode->weight = weight;
        newNode->next = graph[from];
        graph[from] = newNode;

        // Since the graph is undirected, add 'from' to the adjacency list of 'to'
        newNode = malloc(sizeof(struct linkedListNode));
        newNode->index = from;
        newNode->weight = weight;
        newNode->next = graph[to];
        graph[to] = newNode;
    }
}

void printGraph(int lengthVertices, struct linkedListNode *graph[lengthVertices]) {
    printf("Graph (Adjacency List):\n");
    for (int i = 0; i < lengthVertices; i++) {
        printf("%d: ", i);
        struct linkedListNode *current = graph[i];
        while (current != NULL) {
            printf("(%d, %d) ", current->index, current->weight);
            current = current->next;
        }
        printf("\n");
    }
    printf("\n");
}


int leftChild(int index) {
    return index * 2 + 1;
}

int rightChild(int index) {
    return index * 2 + 2;
}

void swap(struct heap *heap, int index1, int index2) {
    struct vertex *temp = heap->array[index2];
    heap->array[index2] = heap->array[index1];
    heap->array[index1] = temp;
}

void heapify(struct heap *heap, int currentIndex) {
    int leftIndex = leftChild(currentIndex);
    int rightIndex = rightChild(currentIndex);
    int temp = currentIndex;
    if (leftIndex <= heap->lastIndex) {
        if (heap->array[leftIndex]->weight < heap->array[temp]->weight) {
            temp = leftIndex;
        }
    }
    if (rightIndex <= heap->lastIndex) {
        if (heap->array[rightIndex]->weight < heap->array[temp]->weight) {
            temp = rightIndex;
        }
    }
    if (temp != currentIndex) {
        swap(heap, temp, currentIndex);
        heapify(heap, temp);
    }
}

int isEmpty(struct heap *heap) {
    if (heap->lastIndex >= 0) {
        return false;
    }
    return true;
}

struct heap *createHeap(int lengthVertices, struct vertex *vertices[lengthVertices]) {
    struct heap *heap = malloc(sizeof(struct heap));
    heap->lastIndex = MAX_VERTICES - 1;

    for (int i = 0; i < lengthVertices; i++) {
        heap->array[i] = vertices[i];
    }

    for (int j = MAX_VERTICES / 2 + 1; j >= 0; j--) {
        heapify(heap, j);
    }
    return heap;
}

void decreaseWeight(struct heap *heap, struct vertex *vertex) {
    // If we know where the node is located in the heap, we could do this in log (n)
    for (int j = heap->lastIndex / 2 + 1; j >= 0; j--) {
        heapify(heap, j);
    }
}

struct vertex *extractMin(struct heap *heap) {
    swap(heap, 0, heap->lastIndex);
    heap->lastIndex--;
    heapify(heap, 0);
    return heap->array[heap->lastIndex + 1];
}

void printPrim(int lengthVertices, struct vertex *vertices[lengthVertices]) {
    printf("Minimum Spanning Tree (Edges and Weights):\n");
    int mstWeight = 0;
    for (int i = 0; i < lengthVertices; i++) {
        if (vertices[i]->predecessor != -1) {
            printf("%d - %d (weight %d)\n", vertices[i]->predecessor, i, vertices[i]->weight);
            mstWeight += vertices[i]->weight;
        }
    }
    printf("Total Weight of MST: %d\n", mstWeight);
}

int primJarnik(int lengthVertices, struct linkedListNode *graph[lengthVertices], int startVertex) {
    struct vertex *currentVertex;
    struct vertex *vertices[lengthVertices];

    for (int i = 0; i < lengthVertices; i++) {
        currentVertex = malloc(sizeof(struct vertex));
        currentVertex->weight = INF;
        currentVertex->partOfMST = false;
        currentVertex->index = i;
        vertices[i] = currentVertex;
    }

    vertices[startVertex]->weight = 0;
    struct heap *heap = createHeap(lengthVertices, vertices);

    int totalWeight = 0;
    struct vertex *extractedVertex;

    while (isEmpty(heap) == false) {
        extractedVertex = extractMin(heap);
        totalWeight += extractedVertex->weight;
        extractedVertex->partOfMST = true;
        struct linkedListNode *llNode = graph[extractedVertex->index];
        while (llNode != NULL) {
            currentVertex = vertices[llNode->index];
            if (currentVertex->partOfMST == false && currentVertex->weight > llNode->weight) {
                currentVertex->weight = llNode->weight;
                currentVertex->predecessor = extractedVertex->index;
                decreaseWeight(heap, currentVertex);
            }
            llNode = llNode->next;
        }
    }
    printPrim(lengthVertices, vertices);
    return totalWeight;
}



int main() {
    int edges[] = {
            0, 1, 4,
            0, 7, 8,
            1, 2, 8,
            1, 7, 11,
            2, 3, 7,
            2, 5, 4,
            2, 8, 2,
            3, 4, 9,
            3, 5, 14,
            4, 5, 10,
            5, 6, 2,
            6, 7, 1,
            6, 8, 6,
            7, 8, 7
    };
    int lengthEdges = (sizeof(edges) / sizeof(edges[0])) / 3;
    int lengthVertices = MAX_VERTICES;

    struct linkedListNode *graph[lengthVertices];
    createGraph(lengthEdges, edges, lengthVertices, graph);
    printGraph(lengthVertices, graph);
    primJarnik(lengthVertices, graph, 0);

    return 0;
}
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

struct heap {
    struct vertex *array[MAX_VERTICES];
    int lastIndex;
};

void
createGraph(int lengthEdges, int edges[lengthEdges], int lengthVertices, int graph[lengthVertices][lengthVertices]) {
    for (int m = 0; m < lengthVertices; m++) {
        for (int n = 0; n < lengthVertices; n++) {
            if (m == n) {
                graph[m][n] = 0;
            } else {
                graph[m][n] = INF;
            }
        }
    }

    for (int i = 0; i < lengthEdges; i++) {
        int from = edges[3 * i];
        int to = edges[3 * i + 1];
        int weight = edges[3 * i + 2];
        graph[from][to] = weight;
        graph[to][from] = weight;
    }
}

void printGraph(int lengthVertices, int graph[lengthVertices][lengthVertices]) {
    printf("Graph:\n");
    for (int m = 0; m < lengthVertices; m++) {
        for (int n = 0; n < lengthVertices; n++) {
            if (graph[m][n] == INF) {
                printf(" X, ");
            } else {
                if (graph[m][n] < 10) {
                    printf(" ");
                }
                printf("%d, ", graph[m][n]);
            }
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
    int graph[lengthVertices][lengthVertices];
    for (int m = 0; m < lengthVertices; m++) {
        for (int n = 0; n < lengthVertices; n++) {
            graph[m][n] = INF;
        }
    }
    for(int i = 0; i < lengthVertices; i++) {
        graph[vertices[i]->predecessor][vertices[i]->index] = vertices[i]->weight;
        graph[vertices[i]->index][vertices[i]->predecessor] = vertices[i]->weight;
    }
    printf("Minimum Spanning Tree ");
    printGraph(lengthVertices, graph);
}

int primJarnik(int lengthVertices, int graph[lengthVertices][lengthVertices], int startVertex) {
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
        for (int i = 0; i < lengthVertices; i++) {
            currentVertex = vertices[i];
            if (currentVertex->partOfMST == false && currentVertex->weight > graph[extractedVertex->index][i]) {
                currentVertex->weight = graph[extractedVertex->index][i];
                currentVertex->predecessor = extractedVertex->index;
                decreaseWeight(heap, currentVertex);
            }
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

    int graph[lengthVertices][lengthVertices];
    createGraph(lengthEdges, edges, lengthVertices, graph);
    printGraph(lengthVertices, graph);
    primJarnik(lengthVertices, graph, 0);

    return 0;
}
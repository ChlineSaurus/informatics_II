#include <stdio.h>
#include <malloc/_malloc.h>

#define MAX_VERTICES 5
#define INF 1000
#define false 0
#define true 1

struct vertex {
    int weight;
    int index;
    int predecessor;
    int visitCount;
};

struct node {
    struct vertex *vertex;
    struct node *next;
};

struct node *head;
struct node *tail;

void newQueue() {
    struct node *temp;
    while (head != NULL) {
        temp = head;
        head = head->next;
        free(temp);
    }
    tail = NULL;
}

int is_empty() {
    if (head == NULL) {
        return true;
    }
    return false;
}

void enqueue(struct vertex *vertex) {
    struct node *newNode = malloc(sizeof(struct node));
    newNode->vertex = vertex;
    newNode->next = NULL;
    if (is_empty() == true) {
        head = newNode;
        tail = newNode;
        return;
    }
    tail->next = newNode;
    tail = newNode;
}

struct vertex *dequeue() {
    if (is_empty() == true) {
        return NULL;
    }
    struct vertex *vertex = head->vertex;
    struct node *temp = head;
    head = head->next;
    free(temp);
    return vertex;
}

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

void printBellmanFord(int lengthVertices, struct vertex *vertices[lengthVertices]) {
    int graph[lengthVertices][lengthVertices];
    for (int m = 0; m < lengthVertices; m++) {
        for (int n = 0; n < lengthVertices; n++) {
            graph[m][n] = INF;
        }
    }
    for (int i = 0; i < lengthVertices; i++) {
        graph[vertices[i]->predecessor][vertices[i]->index] = vertices[i]->weight;
        graph[vertices[i]->index][vertices[i]->predecessor] = vertices[i]->weight;
    }

    printf("Bellman Ford ");
    printGraph(lengthVertices, graph);

    for (int i = 0; i < lengthVertices; i++) {
        printf("Vertex %d: %d\n", vertices[i]->index, vertices[i]->weight);
    }

}

int bellmanFord(int lengthVertices, int graph[lengthVertices][lengthVertices], int startVertex) {
    struct vertex *currentVertex;
    struct vertex *vertices[lengthVertices];
    for (int i = 0; i < lengthVertices; i++) {
        currentVertex = malloc(sizeof(struct vertex));
        currentVertex->weight = INF;
        currentVertex->visitCount = 0;
        currentVertex->index = i;
        vertices[i] = currentVertex;
    }

    vertices[startVertex]->weight = 0;
    newQueue();
    enqueue(vertices[startVertex]);

    while (is_empty() == false) {
        struct vertex *extractedVertex = dequeue();
        extractedVertex->visitCount++;
        if(extractedVertex->visitCount > lengthVertices) {
            printf("There exists a negative cycle!\n");
            return false;
        }

        for(int i = 0; i < lengthVertices; i++) {
            currentVertex = vertices[i];
            int newWeight = extractedVertex->weight + graph[extractedVertex->index][i];
            if(currentVertex->weight > newWeight) {
                currentVertex->weight = newWeight;
                currentVertex->predecessor = extractedVertex->index;
                enqueue(currentVertex);
            }
        }
    }
    printBellmanFord(lengthVertices, vertices);
    return false;
}


int main() {
    int edges[] = {
            0, 1, -1,
            0, 2, 4,
            1, 2, 3,
            1, 3, 3,
            1, 4, 2,
            3, 1, 1,
            3, 2, 5,
            4, 3, -3
    };
    int lengthEdges = (sizeof(edges) / sizeof(edges[0])) / 3;
    int lengthVertices = MAX_VERTICES;

    int graph[lengthVertices][lengthVertices];
    createGraph(lengthEdges, edges, lengthVertices, graph);
    printGraph(lengthVertices, graph);
    bellmanFord(lengthVertices, graph, 0);

    printf("\n\n");
    int edges2[] = {
            0, 1, -1,
            0, 2, 4,
            1, 2, 3,
            1, 3, 3,
            1, 4, 2,
            3, 1, 1,
            2, 3, -5,
            4, 3, -3
    };

    createGraph(lengthEdges, edges2, lengthVertices, graph);
    printGraph(lengthVertices, graph);
    bellmanFord(lengthVertices, graph, 0);

    return 0;
}
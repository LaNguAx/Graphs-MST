#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>

#define INF INT_MAX

// Node structure
typedef struct Node {
    int dest, weight;
    struct Node* next;
} Node;

// Adjacency list structure
typedef struct AdjList {
    Node* head;
} AdjList;

// Graph structure
typedef struct Graph {
    int V;
    AdjList* array;
} Graph;

// Create a new node
Node* createNode(int dest, int weight) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->dest = dest;
    newNode->weight = weight;
    newNode->next = NULL;
    return newNode;
}

// Create a graph
Graph* initializeGraph(int V) {
    Graph* graph = (Graph*)malloc(sizeof(Graph));
    graph->V = V;
    graph->array = (AdjList*)malloc(V * sizeof(AdjList));
    for (int i = 0; i < V; i++) {
        graph->array[i].head = NULL;
    }
    return graph;
}

// Add edge to the graph
void insertEdge(Graph* graph, int src, int dest, int weight) {
    Node* node = createNode(dest, weight);
    node->next = graph->array[src].head;
    graph->array[src].head = node;

    node = createNode(src, weight);
    node->next = graph->array[dest].head;
    graph->array[dest].head = node;
}

// Find the parent of a node
int findParent(int parent[], int i) {
    return (parent[i] == -1) ? i : findParent(parent, parent[i]);
}

// Union of sets
void unionizeSets(int parent[], int x, int y) {
    int xRoot = findParent(parent, x);
    int yRoot = findParent(parent, y);
    if (xRoot != yRoot) {
        parent[xRoot] = yRoot;
    }
}

// Check for cycles
bool checkCycle(Graph* graph, int src, int dest) {
    int* parent = (int*)malloc(graph->V * sizeof(int));
    for (int i = 0; i < graph->V; i++) {
        parent[i] = -1;
    }

    Node* temp;
    for (int v = 0; v < graph->V; v++) {
        temp = graph->array[v].head;
        while (temp) {
            int x = findParent(parent, v);
            int y = findParent(parent, temp->dest);

            if (x == y) {
                free(parent);
                return true;
            }
            unionizeSets(parent, x, y);
            temp = temp->next;
        }
    }
    free(parent);
    return false;
}

// Prim's MST algorithm
Graph* generatePrimMST(Graph* graph) {
    int V = graph->V;
    int* key = (int*)malloc(V * sizeof(int));
    bool* mstSet = (bool*)malloc(V * sizeof(bool));
    int* parent = (int*)malloc(V * sizeof(int));

    for (int i = 0; i < V; i++) {
        key[i] = INF;
        mstSet[i] = false;
    }
    key[0] = 0;
    parent[0] = -1;

    for (int count = 0; count < V - 1; count++) {
        int min = INF, minIndex;
        for (int v = 0; v < V; v++) {
            if (!mstSet[v] && key[v] < min) {
                min = key[v];
                minIndex = v;
            }
        }

        int u = minIndex;
        mstSet[u] = true;

        Node* temp = graph->array[u].head;
        while (temp) {
            int v = temp->dest;
            if (!mstSet[v] && temp->weight < key[v]) {
                key[v] = temp->weight;
                parent[v] = u;
            }
            temp = temp->next;
        }
    }

    Graph* mst = initializeGraph(V);
    for (int i = 1; i < V; i++) {
        insertEdge(mst, parent[i], i, key[i]);
    }

    free(key);
    free(mstSet);
    free(parent);
    return mst;
}

// Print MST
void displayMST(Graph* graph) {
    printf("\nCurrent MST:\n");
    for (int i = 0; i < graph->V; i++) {
        Node* temp = graph->array[i].head;
        while (temp) {
            if (i < temp->dest) {
                printf("Edge: %d - %d (Weight: %d)\n", i, temp->dest, temp->weight);
            }
            temp = temp->next;
        }
    }
}

// Print graph
void displayGraph(Graph* graph) {
    for (int v = 0; v < graph->V; v++) {
        Node* temp = graph->array[v].head;
        printf("Adjacency list of vertex %d: head", v);
        while (temp) {
            printf(" -> %d (Weight: %d)", temp->dest, temp->weight);
            temp = temp->next;
        }
        printf("\n");
    }
}

int main() {
    int V = 20;
    Graph* graph = initializeGraph(V);

    insertEdge(graph, 0, 1, 4);
    insertEdge(graph, 0, 2, 8);
    insertEdge(graph, 1, 2, 11);
    insertEdge(graph, 1, 3, 8);
    insertEdge(graph, 2, 4, 7);
    insertEdge(graph, 2, 5, 4);
    insertEdge(graph, 3, 6, 2);
    insertEdge(graph, 4, 5, 14);
    insertEdge(graph, 4, 7, 10);
    insertEdge(graph, 5, 8, 2);

    printf("Original Graph:\n");
    displayGraph(graph);

    Graph* mst = generatePrimMST(graph);
    displayMST(mst);

    return 0;
}

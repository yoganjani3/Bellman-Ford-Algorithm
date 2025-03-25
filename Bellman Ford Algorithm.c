#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

// Structure to represent an edge
struct Edge {
    int src, dest, weight;
};

// Function declarations
void initializeDistances(int V, int distances[], int source);
void relaxEdges(int V, int E, struct Edge edges[], int distances[]);
int detectNegativeWeightCycle(int E, struct Edge edges[], int distances[]);
void displayResults(int V, int distances[]);
void validateInput(int value, char *message);

// Function to initialize distances
void initializeDistances(int V, int distances[], int source) {
    for (int i = 0; i < V; i++) {
        distances[i] = INT_MAX;
    }
    distances[source] = 0;
    printf("Initialized distances from source vertex %d.\n", source);
}

// Function to relax edges
void relaxEdges(int V, int E, struct Edge edges[], int distances[]) {
    for (int i = 0; i < V - 1; i++) {
        printf("Pass %d of edge relaxation:\n", i + 1);
        for (int j = 0; j < E; j++) {
            int u = edges[j].src;
            int v = edges[j].dest;
            int w = edges[j].weight;

            if (distances[u] != INT_MAX && distances[u] + w < distances[v]) {
                distances[v] = distances[u] + w;
                printf("Relaxing edge (%d -> %d) with weight %d: New distance[%d] = %d\n",
                       u, v, w, v, distances[v]);
            }
        }
    }
}

// Function to detect negative weight cycles
int detectNegativeWeightCycle(int E, struct Edge edges[], int distances[]) {
    for (int j = 0; j < E; j++) {
        int u = edges[j].src;
        int v = edges[j].dest;
        int w = edges[j].weight;

        if (distances[u] != INT_MAX && distances[u] + w < distances[v]) {
            printf("Graph contains a negative weight cycle at edge (%d -> %d) with weight %d.\n",
                   u, v, w);
            return 1; // Indicate presence of negative weight cycle
        }
    }
    return 0; // No negative weight cycle
}

// Function to display results
void displayResults(int V, int distances[]) {
    printf("\nVertex Distance from Source\n");
    printf("---------------------------\n");
    for (int i = 0; i < V; i++) {
        if (distances[i] == INT_MAX) {
            printf("%d\t\tINF\n", i);
        } else {
            printf("%d\t\t%d\n", i, distances[i]);
        }
    }
    printf("---------------------------\n");
}

// Function to validate input
void validateInput(int value, char *message) {
    if (value <= 0) {
        printf("Error: %s must be a positive integer.\n", message);
        exit(EXIT_FAILURE);
    }
}

int main() {
    int V, E;

    printf("Enter the number of vertices: ");
    scanf("%d", &V);
    validateInput(V, "Number of vertices");

    printf("Enter the number of edges: ");
    scanf("%d", &E);
    validateInput(E, "Number of edges");

    struct Edge edges[E];

    printf("Enter edges in the format (source destination weight):\n");
    for (int i = 0; i < E; i++) {
        scanf("%d %d %d", &edges[i].src, &edges[i].dest, &edges[i].weight);
        printf("Edge added: (%d -> %d) with weight %d\n", edges[i].src, edges[i].dest, edges[i].weight);
    }

    int source;
    printf("Enter the source vertex: ");
    scanf("%d", &source);

    int distances[V];
    int choice;

    do {
        printf("\nMenu:\n");
        printf("1. Initialize distances\n");
        printf("2. Relax edges\n");
        printf("3. Detect negative weight cycle\n");
        printf("4. Display results\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                initializeDistances(V, distances, source);
                break;
            case 2:
                relaxEdges(V, E, edges, distances);
                break;
            case 3:
                if (detectNegativeWeightCycle(E, edges, distances)) {
                    printf("Negative weight cycle detected! Algorithm terminated.\n");
                } else {
                    printf("No negative weight cycle detected.\n");
                }
                break;
            case 4:
                displayResults(V, distances);
                break;
            case 5:
                printf("Exiting program.\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 5);

    return 0;
}

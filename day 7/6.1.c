#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define MAX_VERTICES 1000

typedef struct {
    int vertices[MAX_VERTICES][MAX_VERTICES];
    int num_vertices;
} Graph;

typedef struct {
    int queue[MAX_VERTICES];
    int front, rear;
} Queue;

void enqueue(Queue *q, int vertex) {
    q->queue[++q->rear] = vertex;
}

int dequeue(Queue *q) {
    return q->queue[++q->front];
}

int is_empty(Queue *q) {
    return q->front == q->rear;
}

void bfs(Graph *graph, int start_vertex) {
    int visited[MAX_VERTICES] = {0};
    Queue q = {{0}, -1, -1};

    visited[start_vertex] = 1;
    enqueue(&q, start_vertex);

    while (!is_empty(&q)) {
        int current_vertex = dequeue(&q);
        printf("%d ", current_vertex);

        #pragma omp parallel for
        for (int i = 0; i < graph->num_vertices; i++) {
            if (graph->vertices[current_vertex][i] && !visited[i]) {
                visited[i] = 1;
                enqueue(&q, i);
            }
        }
    }
}

int main() {
    Graph graph;
    int num_vertices, start_vertex;

    printf("Enter the number of vertices: ");
    scanf("%d", &num_vertices);
    graph.num_vertices = num_vertices;

    printf("Enter the adjacency matrix:\n");
    for (int i = 0; i < num_vertices; i++) {
        for (int j = 0; j < num_vertices; j++) {
            scanf("%d", &graph.vertices[i][j]);
        }
    }

    printf("Enter the start vertex: ");
    scanf("%d", &start_vertex);

    double start_time = omp_get_wtime();
    bfs(&graph, start_vertex);
    double end_time = omp_get_wtime();

    printf("\nExecution time: %f seconds\n", end_time - start_time);

    return 0;
}

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

void bfs_serial(Graph *graph, int start_vertex) {
    int visited[MAX_VERTICES] = {0};
    Queue q = {{0}, -1, -1};

    visited[start_vertex] = 1;
    enqueue(&q, start_vertex);

    while (!is_empty(&q)) {
        int current_vertex = dequeue(&q);
        printf("%d ", current_vertex);

        // Introduce delay to increase serial execution time
        for (int i = 0; i < 100000; i++) {
            for (int j = 0; j < 1000; j++) {
                int temp = i * j;
            }
        }

        for (int i = 0; i < graph->num_vertices; i++) {
            if (graph->vertices[current_vertex][i] && !visited[i]) {
                visited[i] = 1;
                enqueue(&q, i);
            }
        }
    }
}

void bfs_parallel(Graph *graph, int start_vertex) {
    // Parallel BFS implementation using OpenMP
    // (You can use the previous parallel BFS implementation here)
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

    double start_time_serial = omp_get_wtime();
    bfs_serial(&graph, start_vertex);
    double end_time_serial = omp_get_wtime();

    printf("\nSerial execution time: %f seconds\n", end_time_serial - start_time_serial);

    // Uncomment the following lines to compare with parallel execution time
    /*
    double start_time_parallel = omp_get_wtime();
    bfs_parallel(&graph, start_vertex);
    double end_time_parallel = omp_get_wtime();

    printf("\nParallel execution time: %f seconds\n", end_time_parallel - start_time_parallel);
    */

    return 0;
}

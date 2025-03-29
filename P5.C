#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define INF INT_MAX

typedef struct
{
    int to, weight;
} Edge;

typedef struct
{
    int nodes;
    int **adj;
} Graph;

Graph *createGraph(int n)
{
    Graph *g = (Graph *)malloc(sizeof(Graph));
    g->nodes = n;
    g->adj = (int **)malloc(n * sizeof(int *));
    for (int i = 0; i < n; i++)
    {
        g->adj[i] = (int *)malloc(n * sizeof(int));
        for (int j = 0; j < n; j++)
        {
            g->adj[i][j] = (i == j) ? 0 : INF;
        }
    }
    return g;
}

void addEdge(Graph *g, int u, int v, int w)
{
    g->adj[u][v] = w;
    g->adj[v][u] = w;
}

void removeEdge(Graph *g, int u, int v)
{
    g->adj[u][v] = INF;
    g->adj[v][u] = INF;
}

int *dijkstra(Graph *g, int src)
{
    int *dist = (int *)malloc(g->nodes * sizeof(int));
    int *visited = (int *)malloc(g->nodes * sizeof(int));
    for (int i = 0; i < g->nodes; i++)
    {
        dist[i] = INF;
        visited[i] = 0;
    }
    dist[src] = 0;

    for (int count = 0; count < g->nodes - 1; count++)
    {
        int minDist = INF, u = -1;
        for (int i = 0; i < g->nodes; i++)
        {
            if (!visited[i] && dist[i] < minDist)
            {
                minDist = dist[i];
                u = i;
            }
        }
        if (u == -1)
            break;
        visited[u] = 1;

        for (int v = 0; v < g->nodes; v++)
        {
            if (!visited[v] && g->adj[u][v] != INF && dist[u] + g->adj[u][v] < dist[v])
            {
                dist[v] = dist[u] + g->adj[u][v];
            }
        }
    }
    free(visited);
    return dist;
}

void updateTraffic(Graph *g, int u, int v, int percent)
{
    if (g->adj[u][v] != INF)
    {
        g->adj[u][v] += (g->adj[u][v] * percent) / 100;
        g->adj[v][u] += (g->adj[v][u] * percent) / 100;
    }
}

void interactiveMode(Graph *g)
{
    int choice, u, v, w;

    while (1)
    {
        printf("\n1. Add Edge\n2. Remove Edge\n3. Update Traffic\n4. Find Shortest Path\n5. Exit\nEnter choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            printf("Enter u, v, weight: ");
            scanf("%d %d %d", &u, &v, &w);
            addEdge(g, u, v, w);
            break;
        case 2:
            printf("Enter u, v to remove edge: ");
            scanf("%d %d", &u, &v);
            removeEdge(g, u, v);
            break;
        case 3:
            printf("Enter u, v, traffic increase percent: ");
            scanf("%d %d %d", &u, &v, &w);
            updateTraffic(g, u, v, w);
            break;
        case 4:
        {
            printf("Enter source node: ");
            scanf("%d", &u);
            int *dist = dijkstra(g, u); 

            printf("\nShortest paths from node %d:\n", u);
            for (int i = 0; i < g->nodes; i++)
            {
                printf("To node %d : %d\n", i, dist[i]);
            }
            free(dist);
            break;
        }
        case 5:
            return;
        default:
            printf("Invalid choice!\n");
        }
    }
}

int main()
{
    int n = 5;
    Graph *g = createGraph(n);

    printf("\n==============================================\n");
    printf("Hello! Welcome to Efficient Pathfinding with Real-Time Traffic Adjustments!\n");
    printf("   Find the shortest paths, update traffic conditions, and manage roads dynamically!\n");
    printf("==============================================\n");

    addEdge(g, 0, 1, 10);
    addEdge(g, 1, 2, 20);
    addEdge(g, 2, 3, 30);
    addEdge(g, 3, 4, 40);
    addEdge(g, 1, 4, 50);

    interactiveMode(g);

    for (int i = 0; i < n; i++)
    {
        free(g->adj[i]);
    }
    free(g->adj);
    free(g);
    return 0;
}

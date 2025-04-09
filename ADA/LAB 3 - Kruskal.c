#include <stdio.h>

#define MAX 100
#define INF 9999999 // Represents no connection

typedef struct {
int u, v, w;
} Edge;

int parent[MAX];

// Find set
int find(int i) {
while (parent[i] != i)
i = parent[i];
return i;
}

// Union sets
void union_set(int i, int j) {
int a = find(i);
int b = find(j);
parent[a] = b;
}

int main() {
int cost[MAX][MAX];
Edge edges[MAX * MAX];
int n, i, j, k = 0, totalCost = 0;

printf("Enter number of vertices: ");
scanf("%d", &n);

printf("Enter the adjacency matrix (0 if no edge):\n");
for (i = 0; i < n; i++) {
for (j = 0; j < n; j++) {
scanf("%d", &cost[i][j]);
if (cost[i][j] == 0)
cost[i][j] = INF; // No edge
if (i < j && cost[i][j] != INF) {
edges[k].u = i;
edges[k].v = j;
edges[k].w = cost[i][j];
k++;
}
}
}

// Initialize disjoint sets
for (i = 0; i < n; i++)
parent[i] = i;

// Sort edges by weight (bubble sort)
for (i = 0; i < k - 1; i++) {
for (j = 0; j < k - i - 1; j++) {
if (edges[j].w > edges[j + 1].w) {
Edge temp = edges[j];
edges[j] = edges[j + 1];
edges[j + 1] = temp;
}
}
}

printf("\nEdges in the Minimum Cost Spanning Tree:\n");

for (i = 0; i < k; i++) {
if (find(edges[i].u) != find(edges[i].v)) {
printf("%d - %d : %d\n", edges[i].u, edges[i].v, edges[i].w);
totalCost += edges[i].w;
union_set(edges[i].u, edges[i].v);
}
}

printf("Total cost of MST: %d\n", totalCost);

return 0;
}

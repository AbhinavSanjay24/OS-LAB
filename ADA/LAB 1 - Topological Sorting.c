#include <stdio.h>
#include <stdlib.h>
#define max 100

int adj[max][max];
int indegree[max];
int n;

void calcInDegree() {
    for (int i = 0; i < n; i++) {
        indegree[i] = 0;
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (adj[i][j] == 1) {
                indegree[j]++;
            }
        }
    }
}

void topologicalSort() {
    int queue[max], front = 0, rear = 0;
    int topoOrder[max], index = 0;

    for (int i = 0; i < n; i++) {
        if (indegree[i] == 0) {
            queue[rear++] = i;
        }
    }
    while (front < rear) {
        int v = queue[front++];
        topoOrder[index++] = v;


        for (int i = 0; i < n; i++) {
            if (adj[v][i] == 1) {
                indegree[i]--;
                if (indegree[i] == 0) {
                    queue[rear++] = i;
                }
            }
        }
    }

    if (index != n) {
        printf("Cycle detected! Topological sorting not possible.\n");
        return;
    }
    printf("Topological Order: ");
    for (int i = 0; i < index; i++) {
        printf("%d ", topoOrder[i]);
    }
    printf("\n");
}

int main() {
    printf("Enter number of vertices: ");
    scanf("%d", &n);

    printf("Enter adjacency matrix:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%d", &adj[i][j]);
        }
    }
    calcInDegree();
    topologicalSort();
    return 0;
}

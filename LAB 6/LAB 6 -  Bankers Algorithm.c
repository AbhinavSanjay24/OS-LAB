#include <stdio.h>
#include <stdlib.h>

void main() {
    int n, m, i, j, k;
    int alloc[10][10], max[10][10], need[10][10], avail[10];
    int f[10], ans[10], ind = 0;

    printf("Enter number of processes -- ");
    scanf("%d", &n);

    printf("Enter number of resources -- ");
    scanf("%d", &m);

    for (i = 0; i < n; i++) {
        printf("Enter allocation for P%d -- ", i);
        for (j = 0; j < m; j++)
            scanf("%d", &alloc[i][j]);
        printf("Enter Max -- ");
        for (j = 0; j < m; j++)
            scanf("%d", &max[i][j]);
    }

    printf("Enter Available Resources -- ");
    for (i = 0; i < m; i++)
        scanf("%d", &avail[i]);

    // Calculating need matrix
    for (i = 0; i < n; i++)
        for (j = 0; j < m; j++)
            need[i][j] = max[i][j] - alloc[i][j];

    // Initialize finish array
    for (k = 0; k < n; k++)
        f[k] = 0;

    printf("\n");

    // Banker's Algorithm - Safety Check
    for (k = 0; k < n; k++) {
        for (i = 0; i < n; i++) {
            if (f[i] == 0) {
                int flag = 0;
                for (j = 0; j < m; j++) {
                    if (need[i][j] > avail[j]) {
                        flag = 1;
                        break;
                    }
                }
                if (flag == 0) {
                    ans[ind++] = i;
                    for (j = 0; j < m; j++)
                        avail[j] += alloc[i][j];
                    f[i] = 1;
                    printf("P%d is visited(", i);
                    for (j = 0; j < m; j++)
                        printf("%d ", avail[j]);
                    printf(")\n");
                }
            }
        }
    }

    int safe = 1;
    for (i = 0; i < n; i++) {
        if (f[i] == 0) {
            safe = 0;
            printf("SYSTEM IS NOT IN SAFE STATE\n");
            break;
        }
    }

    if (safe) {
        printf("SYSTEM IS IN SAFE STATE\n");
        printf("The Safe Sequence is -- ");
        for (i = 0; i < n - 1; i++)
            printf("P%d -> ", ans[i]);
        printf("P%d\n", ans[n - 1]);
    }

    // Print Allocation, Max, and Need matrices
    printf("\nProcess    Allocation    Max    Need\n");
    for (i = 0; i < n; i++) {
        printf("P%d\t", i);
        for (j = 0; j < m; j++)
            printf("%d ", alloc[i][j]);
        printf("\t");
        for (j = 0; j < m; j++)
            printf("%d ", max[i][j]);
        printf("\t");
        for (j = 0; j < m; j++)
            printf("%d ", need[i][j]);
        printf("\n");
    }
}

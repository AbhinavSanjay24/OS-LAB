#include <stdio.h>

int main() {
    int n, i, bt[20], wt[20], tat[20];


    printf("Enter total number of processes: ");
    scanf("%d", &n);

    for (i = 0; i < n; i++) {
        printf("Enter Burst Time for Process %d: ", i + 1);
        scanf("%d", &bt[i]);
    }
    float wta = 0, tata = bt[0];

    wt[0] = 0;
    tat[0] = bt[0];
    for (i = 1; i < n; i++) {
        wt[i] = wt[i - 1] + bt[i - 1];
        tat[i] = tat[i - 1] + bt[i];
        wta += wt[i];
        tata += tat[i];
    }
    wta /= n;
    tata /= n;

    printf("\nProcess\tBurst Time\tWaiting Time\tTurnaround Time\n");
    for (i = 0; i < n; i++) {
        printf("P%d\t%d\t\t%d\t\t%d\n", i + 1, bt[i], wt[i], tat[i]);
    }

    printf("\nAverage Waiting Time = %.2f", wta);
    printf("\nAverage Turnaround Time = %.2f", tata);

    return 0;
}

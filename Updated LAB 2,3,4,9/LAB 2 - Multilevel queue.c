#include <stdio.h>

void main() {
    int n, sc = 0, uc = 0, type, bt;
    float wta, tata;

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    int pid[n], sys_id[n], usr_id[n];
    int sys_bt[n], usr_bt[n];
    int bt_all[n], ptype[n];
    int wt[n], tat[n];

    for (int i = 0; i < n; i++) {
        printf("Enter process type (1 for System, 0 for User): ");
        scanf("%d", &type);
        printf("Enter burst time for process %d: ", i + 1);
        scanf("%d", &bt);

        if (type == 1) {
            sys_id[sc] = i + 1;
            sys_bt[sc++] = bt;
        } else {
            usr_id[uc] = i + 1;
            usr_bt[uc++] = bt;
        }
    }

    for (int i = 0; i < sc; i++) {
        pid[i] = sys_id[i];
        bt_all[i] = sys_bt[i];
        ptype[i] = 1;
    }

    for (int i = 0; i < uc; i++) {
        pid[i + sc] = usr_id[i];
        bt_all[i + sc] = usr_bt[i];
        ptype[i + sc] = 0;
    }

    wt[0] = 0;
    tat[0] = bt_all[0];
    wta = wt[0];
    tata = tat[0];

    for (int i = 1; i < n; i++) {
        wt[i] = wt[i - 1] + bt_all[i - 1];
        tat[i] = tat[i - 1] + bt_all[i];
        wta += wt[i];
        tata += tat[i];
    }

    printf("PID\tType\tBT\tWT\tTAT\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\t%d\n", pid[i], ptype[i], bt_all[i], wt[i], tat[i]);
    }

    printf("\nAverage Waiting Time = %.2f", wta / n);
    printf("\nAverage Turnaround Time = %.2f", tata / n);
}

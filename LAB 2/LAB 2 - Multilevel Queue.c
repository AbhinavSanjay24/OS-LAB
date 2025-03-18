#include <stdio.h>
#include <stdlib.h>

struct process {
    int id;
    int burst_time;
    int is_system; // 1 for system, 0 for user
};

typedef struct process Process;

void calculate_scheduling(Process *processes[], int n);

int main() {
    int n, sys_count = 0, user_count = 0;

    printf("Enter the Number of Processes: ");
    scanf("%d", &n);

    if (n <= 0) {
        printf("No Processes to Schedule.\n");
        return 0;
    }

    // Declare two queues for system and user processes
    Process *system_queue[n], *user_queue[n];

    // Input for each process
    for (int i = 0; i < n; i++) {
        int type, burst;
        printf("\nEnter Process Type (System: 1, User: 0): ");
        scanf("%d", &type);
        printf("Enter Burst Time: ");
        scanf("%d", &burst);

        // Dynamically allocate memory for a new process
        Process *p = (Process *)malloc(sizeof(Process));
        p->id = i + 1;
        p->burst_time = burst;
        p->is_system = type;

        // Add the process to the respective queue
        if (type == 1) {
            system_queue[sys_count++] = p;
        } else {
            user_queue[user_count++] = p;
        }
    }

    // Merge system and user processes into a single list for scheduling
    Process *processes[n];
    int index = 0;

    // First, add all system processes to the list (higher priority)
    for (int i = 0; i < sys_count; i++) {
        processes[index++] = system_queue[i];
    }

    // Then, add all user processes to the list
    for (int i = 0; i < user_count; i++) {
        processes[index++] = user_queue[i];
    }

    // Calculate the scheduling for the combined processes
    calculate_scheduling(processes, n);

    // Free dynamically allocated memory for system and user processes
    for (int i = 0; i < sys_count; i++) {
        free(system_queue[i]);
    }

    for (int i = 0; i < user_count; i++) {
        free(user_queue[i]);
    }

    return 0;
}

void calculate_scheduling(Process *processes[], int n) {
    int waiting_time[n], turnaround_time[n];
    float total_wt = 0, total_tat = 0;

    // The first process has 0 waiting time
    waiting_time[0] = 0;
    turnaround_time[0] = processes[0]->burst_time;

    // Accumulate total waiting time and turnaround time
    total_wt = waiting_time[0];
    total_tat = turnaround_time[0];

    for (int i = 1; i < n; i++) {
        waiting_time[i] = waiting_time[i - 1] + processes[i - 1]->burst_time;
        turnaround_time[i] = waiting_time[i] + processes[i]->burst_time;
        total_wt += waiting_time[i];
        total_tat += turnaround_time[i];
    }

    // Print the process details
    printf("\nProcess\t Type\t Burst Time\t Waiting Time\t Turnaround Time\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t %s\t %d\t\t %d\t\t %d\n",
               processes[i]->id,
               processes[i]->is_system ? "System" : "User",
               processes[i]->burst_time,
               waiting_time[i],
               turnaround_time[i]);
    }

    // Calculate and print average waiting time and turnaround time
    printf("\nAverage Waiting Time = %.2f", total_wt / n);
    printf("\nAverage Turnaround Time = %.2f\n", total_tat / n);
}

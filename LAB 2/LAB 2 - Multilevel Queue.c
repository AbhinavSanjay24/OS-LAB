#include <stdio.h>

void main() {
    int num_processes, system_count = 0, user_count = 0, process_type, burst_time;
    float avg_waiting_time, avg_turnaround_time;

    // Get the number of processes from the user
    printf("Enter the number of processes: ");
    scanf("%d", &num_processes);

    // Declare arrays for storing process data
    int process_ids[num_processes];
    int system_process_ids[num_processes], user_process_ids[num_processes];
    int system_burst_times[num_processes], user_burst_times[num_processes];
    int burst_times[num_processes], process_types[num_processes];
    int waiting_times[num_processes], turnaround_times[num_processes];

    // Input process details
    for (int i = 0; i < num_processes; i++) {
        printf("Enter process type (1 for System, 0 for User): ");
        scanf("%d", &process_type);
        printf("Enter burst time for process %d: ", i + 1);
        scanf("%d", &burst_time);

        if (process_type == 1) {  // System process
            system_process_ids[system_count] = i + 1;
            system_burst_times[system_count++] = burst_time;
        } else {  // User process
            user_process_ids[user_count] = i + 1;
            user_burst_times[user_count++] = burst_time;
        }
    }

    // Populate process data for system processes
    for (int i = 0; i < system_count; i++) {
        process_ids[i] = system_process_ids[i];
        burst_times[i] = system_burst_times[i];
        process_types[i] = 1;  // System process
    }

    // Populate process data for user processes
    for (int i = 0; i < user_count; i++) {
        process_ids[i + system_count] = user_process_ids[i];
        burst_times[i + system_count] = user_burst_times[i];
        process_types[i + system_count] = 0;  // User process
    }

    // Initialize the waiting time and turnaround time for the first process
    waiting_times[0] = 0;
    turnaround_times[0] = burst_times[0];
    avg_waiting_time = waiting_times[0];
    avg_turnaround_time = turnaround_times[0];

    // Calculate waiting time and turnaround time for each process
    for (int i = 1; i < num_processes; i++) {
        waiting_times[i] = waiting_times[i - 1] + burst_times[i - 1];
        turnaround_times[i] = turnaround_times[i - 1] + burst_times[i];
        avg_waiting_time += waiting_times[i];
        avg_turnaround_time += turnaround_times[i];
    }

    // Output the process details
    printf("Process ID\tProcess Type\tBurst Time\tWaiting Time\tTurnaround Time\n");
    for (int i = 0; i < num_processes; i++) {
        printf("%d\t\t%d\t\t%d\t\t%d\t\t%d\n",
               process_ids[i], process_types[i], burst_times[i],
               waiting_times[i], turnaround_times[i]);
    }

    // Output average waiting time and average turnaround time
    printf("\nAverage waiting time = %.2f", avg_waiting_time / num_processes);
    printf("\nAverage turnaround time = %.2f", avg_turnaround_time / num_processes);
}

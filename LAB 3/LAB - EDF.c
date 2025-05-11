#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int id, period, execution_time, deadline, executed;
} Task;

int compare_tasks(const void *a, const void *b) {
    return ((Task *)a)->deadline - ((Task *)b)->deadline;
}

void edf_schedule(Task *tasks, int n, int total_time) {
    printf("Time\t");
    for (int i = 0; i < n; i++) printf("Task %d\t", tasks[i].id);
    printf("\n");

    for (int t = 0; t < total_time; t++) {
        printf("%d\t", t);
        int exec = -1;

        for (int i = 0; i < n; i++)
            if (t % tasks[i].period == 0)
                tasks[i].deadline = t + tasks[i].period, tasks[i].executed = 0;

        qsort(tasks, n, sizeof(Task), compare_tasks);

        for (int i = 0; i < n; i++)
            if (t < tasks[i].deadline && tasks[i].executed < tasks[i].execution_time) {
                exec = i;
                tasks[i].executed++;
                break;
            }

        for (int i = 0; i < n; i++) printf(i == exec ? "Exec\t" : "\t");
        printf("\n");
    }
}

int main() {
    int n, total_time;
    printf("Enter number of tasks: ");
    scanf("%d", &n);

    Task *tasks = malloc(n * sizeof(Task));
    for (int i = 0; i < n; i++) {
        tasks[i].id = i + 1;
        printf("Period and execution time for Task %d: ", i + 1);
        scanf("%d %d", &tasks[i].period, &tasks[i].execution_time);
        tasks[i].deadline = tasks[i].period;
        tasks[i].executed = 0;
    }

    printf("Enter total time: ");
    scanf("%d", &total_time);

    printf("\nEarliest Deadline First Scheduling:\n");
    edf_schedule(tasks, n, total_time);
    free(tasks);
    return 0;
}





/*#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int id;
    int period;
    int execution_time;
    int deadline;
    int executed;
} Task;

int compare_tasks(const void *a, const void *b) {
    return ((Task *)a)->deadline - ((Task *)b)->deadline;
}

void earliest_deadline_first_scheduling(Task tasks[], int num_tasks, int total_time) {
    // Header of the table
    printf("Time\t");
    for (int i = 0; i < num_tasks; i++)
        printf("Task %d\t", tasks[i].id);
    printf("\n");

    // Iterate through time
    for (int current_time = 0; current_time < total_time; current_time++) {
        printf("%d\t", current_time);
        int executed_task = -1;

        for (int i = 0; i < num_tasks; i++) {
            // Refresh deadline and execution time counter
            if (current_time % tasks[i].period == 0) {
                tasks[i].deadline = current_time + tasks[i].period;
                tasks[i].executed = 0;
            }
        }

        // Sort tasks by earliest deadline
        qsort(tasks, num_tasks, sizeof(Task), compare_tasks);

        for (int i = 0; i < num_tasks; i++) {
            if (current_time < tasks[i].deadline && tasks[i].executed < tasks[i].execution_time) {
                executed_task = i;
                tasks[i].executed++;
                break;
            }
        }

        // Print execution result
        for (int i = 0; i < num_tasks; i++) {
            if (i == executed_task) {
                printf("Exec\t");
            } else {
                printf("\t");
            }
        }
        printf("\n");
    }
}

int main() {
    int num_tasks, total_time;

    printf("Enter the number of tasks: ");
    scanf("%d", &num_tasks);

    Task *tasks = (Task *)malloc(num_tasks * sizeof(Task));
    if (tasks == NULL) {
        printf("Memory allocation failed.\n");
        return 1;
    }

    for (int i = 0; i < num_tasks; i++) {
        tasks[i].id = i + 1;
        printf("Enter period for Task %d: ", i + 1);
        scanf("%d", &tasks[i].period);
        printf("Enter execution time for Task %d: ", i + 1);
        scanf("%d", &tasks[i].execution_time);
        tasks[i].deadline = tasks[i].period; // initial deadline
        tasks[i].executed = 0;               // reset executed time
    }

    printf("Enter total time for scheduling: ");
    scanf("%d", &total_time);

    printf("\nScheduling using Earliest Deadline First:\n");
    earliest_deadline_first_scheduling(tasks, num_tasks, total_time);

    free(tasks);
    return 0;
}*/



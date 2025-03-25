#include <stdio.h>
#include <stdlib.h>

#define MAX_TASKS 10

typedef struct {
    int id;
    int TimePeriod;
    int execution_time;
    int remaining_time;
    int next_release;
} Task;

void rms_scheduling(Task tasks[], int n, int total_time) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (tasks[j].TimePeriod > tasks[j + 1].TimePeriod) {
                Task temp = tasks[j];
                tasks[j] = tasks[j + 1];
                tasks[j + 1] = temp;
            }
        }
    }

    for (int i = 0; i < n; i++) {
        tasks[i].remaining_time = 0;
        tasks[i].next_release = 0;
    }

    for (int t = 0; t < total_time; t++) {
        Task *current_task = NULL;

        for (int i = 0; i < n; i++) {
            if (t == tasks[i].next_release) {
                tasks[i].remaining_time = tasks[i].execution_time;
                tasks[i].next_release += tasks[i].TimePeriod;
            }
        }

        for (int i = 0; i < n; i++) {
            if (tasks[i].remaining_time > 0) {
                current_task = &tasks[i];
                break;
            }
        }

        if (current_task != NULL) {
            printf("Time %d: Executing Task %d\n", t, current_task->id);
            current_task->remaining_time--;
        } else {
            printf("Time %d: Idle\n", t);
        }
    }
}

int main() {
    int num_tasks;
    printf("Enter number of tasks: ");
    scanf("%d", &num_tasks);

    Task tasks[MAX_TASKS];

    for (int i = 0; i < num_tasks; i++) {
        printf("Enter Task %d ID, Execution Time, and Time Period: ", i + 1);
        scanf("%d %d %d", &tasks[i].id, &tasks[i].execution_time, &tasks[i].TimePeriod);
        tasks[i].remaining_time = 0;
        tasks[i].next_release = 0;
    }

    int total_time;
    printf("Enter total scheduling time: ");
    scanf("%d", &total_time);

    rms_scheduling(tasks, num_tasks, total_time);
    return 0;
}

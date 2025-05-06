#include <stdio.h>
#include <stdbool.h>
#define DISK_SIZE 100
int main() {
    int disk[DISK_SIZE] = {0};
    int start, length, i, choice;
    printf("Sequential File Allocation Simulation\n");
    while (1) {
        printf("\nEnter starting block and length of the file: ");
        scanf("%d%d", &start, &length);
        if (start < 0 || start >= DISK_SIZE || (start + length) > DISK_SIZE) {
            printf("Invalid input. Blocks out of disk range.\n");
        } else {
            bool allocated = true;
            for (i = start; i < start + length; i++) {
                if (disk[i] == 1) {
                    allocated = false;
                    break;
                }
            }
            if (allocated) {
                for (i = start; i < start + length; i++) {
                    disk[i] = 1;
                }
                printf("File allocated successfully from block %d to %d.\n", start, start + length - 1);
            } else {
                printf("File cannot be allocated. Some blocks are already occupied.\n");
            }
        }
        printf("Do you want to allocate another file? (1 for Yes / 0 for No): ");
        scanf("%d", &choice);
        if (choice == 0) break;
    }
    printf("\nFinal Disk Status:\n");
    for (i = 0; i < DISK_SIZE; i++) {
        printf("%d", disk[i]);
    }
    printf("\n");
    return 0;
}

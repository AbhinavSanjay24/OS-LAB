#include <stdio.h>
#include <stdlib.h>

#define MAX_BLOCKS 100
#define MAX_PROCESSES 100

// Structure to represent a memory block
typedef struct {
    int size;
    int allocated; // 0 = free, 1 = allocated
} Block;

// Function to perform First-Fit allocation
void firstFit(Block blocks[], int nBlocks, int processes[], int nProcesses) {
    printf("\nFirst-Fit Allocation:\n");
    for (int i = 0; i < nProcesses; i++) {
        int allocated = 0;
        for (int j = 0; j < nBlocks; j++) {
            if (!blocks[j].allocated && blocks[j].size >= processes[i]) {
                printf("Process %d of size %d allocated to Block %d of size %d\n",
                       i + 1, processes[i], j + 1, blocks[j].size);
                blocks[j].allocated = 1;
                blocks[j].size -= processes[i];
                allocated = 1;
                break;
            }
        }
        if (!allocated)
            printf("Process %d of size %d not allocated\n", i + 1, processes[i]);
    }
}

// Function to perform Best-Fit allocation
void bestFit(Block blocks[], int nBlocks, int processes[], int nProcesses) {
    printf("\nBest-Fit Allocation:\n");
    for (int i = 0; i < nProcesses; i++) {
        int bestIndex = -1;
        for (int j = 0; j < nBlocks; j++) {
            if (!blocks[j].allocated && blocks[j].size >= processes[i]) {
                if (bestIndex == -1 || blocks[j].size < blocks[bestIndex].size)
                    bestIndex = j;
            }
        }
        if (bestIndex != -1) {
            printf("Process %d of size %d allocated to Block %d of size %d\n",
                   i + 1, processes[i], bestIndex + 1, blocks[bestIndex].size);
            blocks[bestIndex].allocated = 1;
            blocks[bestIndex].size -= processes[i];
        } else {
            printf("Process %d of size %d not allocated\n", i + 1, processes[i]);
        }
    }
}

// Function to perform Worst-Fit allocation
void worstFit(Block blocks[], int nBlocks, int processes[], int nProcesses) {
    printf("\nWorst-Fit Allocation:\n");
    for (int i = 0; i < nProcesses; i++) {
        int worstIndex = -1;
        for (int j = 0; j < nBlocks; j++) {
            if (!blocks[j].allocated && blocks[j].size >= processes[i]) {
                if (worstIndex == -1 || blocks[j].size > blocks[worstIndex].size)
                    worstIndex = j;
            }
        }
        if (worstIndex != -1) {
            printf("Process %d of size %d allocated to Block %d of size %d\n",
                   i + 1, processes[i], worstIndex + 1, blocks[worstIndex].size);
            blocks[worstIndex].allocated = 1;
            blocks[worstIndex].size -= processes[i];
        } else {
            printf("Process %d of size %d not allocated\n", i + 1, processes[i]);
        }
    }
}

// Function to reset all memory blocks for fresh use
void resetBlocks(Block dest[], Block src[], int n) {
    for (int i = 0; i < n; i++) {
        dest[i].size = src[i].size;
        dest[i].allocated = 0;
    }
}

int main() {
    int nBlocks, nProcesses;
    Block originalBlocks[MAX_BLOCKS], blocks[MAX_BLOCKS];
    int processes[MAX_PROCESSES];

    printf("Enter number of memory blocks: ");
    scanf("%d", &nBlocks);
    printf("Enter sizes of memory blocks:\n");
    for (int i = 0; i < nBlocks; i++) {
        scanf("%d", &originalBlocks[i].size);
        originalBlocks[i].allocated = 0;
    }

    printf("Enter number of processes: ");
    scanf("%d", &nProcesses);
    printf("Enter sizes of processes:\n");
    for (int i = 0; i < nProcesses; i++) {
        scanf("%d", &processes[i]);
    }

    resetBlocks(blocks, originalBlocks, nBlocks);
    firstFit(blocks, nBlocks, processes, nProcesses);

    resetBlocks(blocks, originalBlocks, nBlocks);
    bestFit(blocks, nBlocks, processes, nProcesses);

    resetBlocks(blocks, originalBlocks, nBlocks);
    worstFit(blocks, nBlocks, processes, nProcesses);

    return 0;
}

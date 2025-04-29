#include <stdio.h>
#define MAX 100

// Function to check if page is present
int isPresent(int frames[], int page, int n) {
    for (int i = 0; i < n; i++)
        if (frames[i] == page)
            return 1;
    return 0;
}

// FIFO Page Replacement
void FIFO(int pages[], int n, int capacity) {
    int frames[capacity], front = 0, count = 0;
    printf("\nFIFO Page Replacement Process:\n");
    for (int i = 0; i < n; i++) {
        if (!isPresent(frames, pages[i], capacity)) {
            frames[front] = pages[i];
            front = (front + 1) % capacity;
            count++;
            printf("PF No. %d: ", count);
            for (int j = 0; j < capacity; j++)
                printf("%c ", (j < count) ? frames[j] + '0' : '-');
            printf("\n");
        }
    }
    printf("FIFO Page Faults: %d\n", count);
}

// LRU Page Replacement
void LRU(int pages[], int n, int capacity) {
    int frames[capacity], recent[capacity], count = 0;
    for (int i = 0; i < capacity; i++) frames[i] = -1;
    for (int i = 0; i < capacity; i++) recent[i] = -1;

    printf("\nLRU Page Replacement Process:\n");
    for (int i = 0; i < n; i++) {
        int found = 0;
        // Check if the page is already in any of the frames
        for (int j = 0; j < capacity; j++) {
            if (frames[j] == pages[i]) {
                found = 1;
                recent[j] = i;  // Update the recent access time
                break;
            }
        }

        if (!found) {  // If page not found in frames, replace a page
            int least = 0;
            // Find the page with the least recent access time
            for (int j = 1; j < capacity; j++) {
                if (recent[j] < recent[least]) {
                    least = j;
                }
            }

            frames[least] = pages[i];  // Replace the least recently used page
            recent[least] = i;  // Update the access time for the replaced page
            count++;  // Increment page fault count

            // Print the current state of the frames
            printf("PF No. %d: ", count);
            for (int j = 0; j < capacity; j++) {
                printf("%c ", frames[j] == -1 ? '-' : frames[j] + '0');
            }
            printf("\n");
        }
    }
    printf("LRU Page Faults: %d\n", count);
}

// Optimal Page Replacement
void Optimal(int pages[], int n, int capacity) {
    int frames[capacity], count = 0;
    for (int i = 0; i < capacity; i++) frames[i] = -1;

    printf("\nOptimal Page Replacement Process:\n");
    for (int i = 0; i < n; i++) {
        if (!isPresent(frames, pages[i], capacity)) {
            int index = -1, farthest = i;
            for (int j = 0; j < capacity; j++) {
                int k;
                for (k = i + 1; k < n; k++) {
                    if (frames[j] == pages[k]) break;
                }
                if (k > farthest) {
                    farthest = k;
                    index = j;
                }
            }

            if (index == -1)
                index = 0;

            frames[index] = pages[i];
            count++;
            printf("PF No. %d: ", count);
            for (int j = 0; j < capacity; j++)
                printf("%c ", frames[j] == -1 ? '-' : frames[j] + '0');
            printf("\n");
        }
    }
    printf("Optimal Page Faults: %d\n", count);
}

int main() {
    int capacity, n, pages[MAX];

    printf("Enter the number of Frames: ");
    scanf("%d", &capacity);

    printf("Enter the length of reference string: ");
    scanf("%d", &n);

    printf("Enter the reference string: ");
    for (int i = 0; i < n; i++)
        scanf("%d", &pages[i]);

    FIFO(pages, n, capacity);
    LRU(pages, n, capacity);
    Optimal(pages, n, capacity);

    return 0;
}

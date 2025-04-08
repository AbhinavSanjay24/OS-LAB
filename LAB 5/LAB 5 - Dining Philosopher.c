#include <stdio.h>
#include <stdlib.h>

#define N 5
#define THINKING 0
#define HUNGRY 1
#define EATING 2

int state[N]={0};
int forks[N]={0};
int hungry[N]={0};

int left(int id){
    return(id+N-1)%N;
}

int right(int id){
    return(id+1)%N;
}

int can_eat(int id){
    return forks[id]==0 && forks[right(id)]==0;
}

void eat(int id){
    forks[id]=1;
    forks[right(id)]=1;
    state[id]=EATING;
    printf("P %d is granted to eat\n", id+1);
    printf("P %d has finished eating\n", id+1);
    forks[id]=0;
    forks[right(id)]=0;
    state[id]=THINKING;
}

void simulate(int max_eaters){
    int eating_count=0;

    for (int i=0; i<N && eating_count<max_eaters; i++){
        if (hungry[i]){
            printf("P %d is waiting\n", i+1);
        }
    }

    for(int i=0; i<N && eating_count<max_eaters; i++){
        if (hungry[i] && can_eat(i)) {
            eat(i);
            hungry[i]=0;
            eating_count++;
        }
    }
}

void main() {
    int total, hungry_count, id, choice;

    printf("Total number of philosophers: ");
    scanf("%d", &total);

    printf("How many are hungry: ");
    scanf("%d", &hungry_count);

    for (int i=0; i<hungry_count; i++) {
        printf("Enter philosopher %d position (1 to %d): ", i+1, total);
        scanf("%d", &id);
        hungry[id-1]=1;
        state[id-1]=HUNGRY;
    }

    while (1) {
        printf("\n1. One can eat at a time\n");
        printf("2. Two can eat at a time\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        if (choice==3) break;
        if (choice==1 || choice==2) {
            simulate(choice);
        }
        else {
            printf("Invalid choice!\n");
        }
    }
}

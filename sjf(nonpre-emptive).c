#include <stdio.h>
int n;
float totaltat = 0,totalwt = 0;
struct Process {
    int pid;
    int at;
    int bt;
    int ct;
    int tat;
    int wt;
}p[100];

void sortByArrival() {
    struct Process temp;
    for(int i=0; i<n-1; i++) {
        for(int j=0; j<n-i-1; j++) {
            if(p[j].at > p[j+1].at) {
                temp = p[j];
                p[j] = p[j+1];
                p[j+1] = temp;
            }
        }
    }
}
void calct(){
    p[0].ct = p[0].at + p[0].bt;
    for(int i=1; i<n; i++){
        if(p[i].at > p[i-1].ct){
            p[i].ct = p[i].at + p[i].bt;
        }
        else{
            p[i].ct = p[i-1].ct + p[i].bt;
        }
    }
}
void calttwt(){
    for(int i=0; i<n; i++){
        p[i].tat = p[i].ct - p[i].at;
        totaltat += p[i].tat;
        p[i].wt = p[i].tat - p[i].bt;
        totalwt += p[i].wt;
    }
}
int main() {
    printf("enter no. of processes\n");
    scanf("%d",&n);
    printf("enter arrival time and burst time of %d processes\n",n);
    for(int i=0; i<n; i++)
    {
        p[i].pid = i + 1;
        scanf("%d%d",&p[i].at,&p[i].bt);
    }
    sortByArrival();
    calct();
    calttwt();
    printf("\nSJF SCHEDULING (non-preemptive)\n");
    printf("PID\tAT\tBT\tCT\tTAT\tWT\n");
    for(int i=0; i<n; i++) {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\n", p[i].pid, p[i].at, p[i].bt, p[i].ct, p[i].tat, p[i].wt);
    }

    printf("\nAverage Turnaround Time: %.2f\n", totaltat/n);
    printf("Average Waiting Time: %.2f\n", totalwt/n);

    return 0;
}

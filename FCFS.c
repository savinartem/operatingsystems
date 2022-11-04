#include <stdio.h>
#include <stdlib.h>

// NUmbers of processes  
const int NUM_PROCESS=10;

// add data about proces
struct Processes
{
    int pid;
    int arrival;
    int waiting;
    int burst;/* Service Time */
    int turnaround;
    int starttime;
    int finishtime;
};

int main(int argc, char* argv[])
{
    float sum=0;
    float avg=0;

    
    struct Processes *p;

    //allocate memory for struct pointer
     p=(struct Processes*) malloc(NUM_PROCESS*sizeof(struct Processes));    

    printf("Enter information about every process: Arrival time and Burst time:\n");

    //-----------------------end input data--------------------------------------
    for (int i=0; i<NUM_PROCESS;++i)
    {
        printf("Pricess %d \n", i+1);
        printf("Arrival time & Burst time: ");
        scanf("%d %d", &(p+i)->arrival, &(p+i)->burst);
        (p+i)->pid=i+1;
        printf("---------------------------------- \n");
    }
    //-----------------------end input data--------------------------------------
  
    //------------------------print struct---------------------------------------
    printf("\nYour input:\n");
    printf("-------------------------------------------------------------\n");
    for(int i=0; i<NUM_PROCESS;++i)
    {
        printf("Arrival: %d\tBurst: %d \tPID#: %d\n",(p+i)->arrival,(p+i)->burst,(p+i)->pid);
    }
     //------------------------end print struct---------------------------------------
    
    //-----------------------sorting arrival time--------------------------------
      for (int i=0;i<NUM_PROCESS;i++)
    {
        struct Processes temp;
        for (int j=i+1; j<NUM_PROCESS;j++)
        {
            if ((p+j)->arrival<(p+i)->arrival)
            {
               temp=*(p+i);
               *(p+i)=*(p+j);
               *(p+j)=temp;
            }
        }
    }
    //-----------------------end sorting arrival time--------------------------------

    printf("\nSorted Data by arrived time:\n");
    printf("-------------------------------------------------------------\n");

    //print 
    for(int i=0; i<NUM_PROCESS;++i)
    {
         printf("PID#: %d\tArrival: %d\tBurst: %d \tWait: %d\n",(p+i)->pid,(p+i)->arrival,(p+i)->burst,(p+i)->waiting);
    }
   

    //---------------start time---------------------------------------
    p->starttime=p->arrival;
    p->finishtime=p->starttime+p->burst;
    for(int i=1; i<NUM_PROCESS; i++)
    {   
        if((p+i-1)->finishtime<(p+i)->arrival)
        {
            (p+i)->starttime=(p+i)->arrival;
        }
        else
        {
        (p+i)->starttime=(p+i-1)->finishtime;
        }
        (p+i)->finishtime=(p+i)->starttime+(p+i)->burst;
        
    }
    //---------------end start time------------------------------------

    //----------------turnaround time -----------------------------
    for(int i=0; i<NUM_PROCESS;i++)
    {
        //(p+i)->turnaround=(p+i)->burst+(p+i)->arrival;
        (p+i)->turnaround=(p+i)->finishtime-(p+i)->arrival;
    }
    //----------------end turnaround time ----------------------------

     //----------------waiting time------------------------------------
    p->waiting=0;
    for(int i=1; i<NUM_PROCESS;i++)
    {
        (p+i)->waiting=(p+i)->turnaround-(p+i)->burst;
       //(p+i)->waiting=(p+i)->starttime-(p+i)->arrival;
       
    }
    //----------------end waiting time--------------------------------


    // --------------sum of turnaround time & AVG---------------------- 
    for (int i=0; i<NUM_PROCESS;i++)
    {
    sum+=(p+i)->turnaround;
    }
    // find avg time
    avg=sum/NUM_PROCESS;
    // --------------end sum of turnaround time & AVG--------------------
  
    printf("\n-------------------------------------------------------------\n");
    printf("PID\tArrival\tBurst\tStart\tWaiting\tFinish\tTurnArround\n");

    for(int i=0; i<NUM_PROCESS; i++)
    {
        printf("%d\t %d\t %d\t %d\t %d\t %d\t %d\n",
        (p+i)->pid,
        (p+i)->arrival,
         (p+i)->burst,
          (p+i)->starttime,
          (p+i)->waiting,
          (p+i)->finishtime,
           (p+i)->turnaround);
    }
    printf("-------------------------------------------------------------\n");
    printf ("Average Turnaround Time: %.3f\n", avg);


    return 0;
}

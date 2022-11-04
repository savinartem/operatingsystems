/*
	Classic problem with bridge and 2 villedges 
	using C and pthread.h lib


*/



// note for compile use "gcc as3.c -pthread -o test"
#include <stdio.h>
#include <stdlib.h>// use for srand()
#include <unistd.h>// use for sleep
#include <pthread.h>

#define NUM_THREADS 3

    /*  Global vars */
pthread_mutex_t mutex;
int northCount=1;//start count from 1st farmer
int southCount=1;


/*  Function to pass bridge from south or north side    */
void passBridge(char arr[], int farmerCount)
{
    srand(time(NULL));
    printf("%s Tunbridge #%d farmer is traveling on the bridge...\n", arr, farmerCount);
    //sleep for random period (up 3sec)
    sleep(rand()%4);
} 


    /*  north thread function   */
void* northThread()
{
    /* acquire mutex lock */
     pthread_mutex_lock(&mutex);

    printf("North Tunbridge #%d farmer can cross the bridge\n", northCount);
    passBridge("North",northCount);
    printf("North Tunbridge #%d farmer has left the bridge\n\n", northCount);
    northCount++;

    /* release mutex lock */
    pthread_mutex_unlock(&mutex);
    /* terminate calling thread */
    pthread_exit(0);
}


/*  south thread function */
void* southThread()
{
    /* acquire mutex lock */
    pthread_mutex_lock(&mutex);

    printf("South Tunbridge #%d farmer can cross the bridge\n", southCount);
    passBridge("South",southCount);
    printf("South Tunbridge #%d farmer has left the bridge\n\n", southCount);
    southCount++;

    /* release mutex lock */
    pthread_mutex_unlock(&mutex);
     /* terminate calling thread */
    pthread_exit(0);
}


int main(int argc, char* argv[])
{
    pthread_t northPt[NUM_THREADS];
    pthread_t southPt[NUM_THREADS];

    /*  create mutex lock       */
    pthread_mutex_init(&mutex, NULL);

    /*      crearing threads    */
    for(int i=0; i<NUM_THREADS;i++)
    {
        if(pthread_create(northPt+i, NULL, &northThread, NULL) !=0)
        {
            perror("Failed to create thread");
            return 1;
        }
         if(pthread_create(southPt+i, NULL, &southThread, NULL) !=0)
        {
            perror("Failed to create thread");
            return 1;
        }
    }

    /*   join threads    */
    for (int i=0; i<NUM_THREADS;i++)
    {
        if(pthread_join(northPt[i], NULL)!=0)
        {
            perror("Failed to join thread");
                return 2;
        }
            if(pthread_join(southPt[i], NULL) !=0)
            {
                perror("Failed to join thread");
                    return 2;
            }
    }

    /*  Deletes a mutex object  */
    pthread_mutex_destroy(&mutex);

    return 0;
}

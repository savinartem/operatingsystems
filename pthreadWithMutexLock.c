/*

	multithreaded app
	using pthred.h lib

*/


#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <time.h>   // for clock_t, clock(), CLOCKS_PER_SEC
#include <unistd.h> //for sleep()

// Global vars
int num;
int maxDivisirs=1;//// Max number of divisors 
int numWithMax=1;
/*
    using as the lock, with out it I got different values evrytime program was run 
    mutex protect selected part of code from another thread when that part of code
    executed by one thread
*/
pthread_mutex_t mutex; 

void* calculation()
{
for(num=2; num<=10000;num++)
{
    int testNum;//A number to be tested to see if it's a divisor of N.
    int divisorCount=0;//// Number of divisors of N
    
    pthread_mutex_lock(&mutex);//lock mutex

    for(testNum=1; testNum<=num;testNum++)
    {
        if(num%testNum==0)
        {
            divisorCount++;
        }
    }
    if(divisorCount>maxDivisirs)
    {
        maxDivisirs=divisorCount;
        numWithMax=num;
    }
    //after one thread finished unlock mutex
    pthread_mutex_unlock(&mutex);
}
}

int main(int argc, char* argv[]){
    // to store the execution time of code
    double time_spend = 0.0;
    pthread_t pt[8];
    printf("CPU cores of current machine:\n"); 
    /*
    *   To check # of cores on the system using system command
    *   "cat /proc/cpuinfo | grep processor | wc -l" 
    */
    system("cat /proc/cpuinfo | grep processor | wc -l");
    
    clock_t begin=clock();
    // initialize mutex
     pthread_mutex_init(&mutex, NULL);
      for (int i = 0; i < 8; i++) {
        if (pthread_create(pt + i, NULL, &calculation, NULL) != 0) {
            perror("Failed to create thread");
            return 1;
        }
        printf("Thread %d has started\n", i+1);
    }
    pthread_mutex_destroy(&mutex);
    for (int i = 0; i < 8; i++) {
        if (pthread_join(pt[i], NULL) != 0) {
            perror("Failed to join thread");
            return 2;
        }
        printf("Thread %d has finished execution\n", i+1);
    }
    clock_t end=clock();
    // calculate elapsed time by finding difference (end - begin) and
    // dividing the difference by CLOCKS_PER_SEC to convert to seconds
    time_spend+=(double)(end-begin)/CLOCKS_PER_SEC;
    printf("The elapsed time is %f seconds\n", time_spend);
    printf("Max divisorsis %d\n",maxDivisirs);
    printf("integer with largest # of divisor is %d\n", numWithMax);
    return 0;
}

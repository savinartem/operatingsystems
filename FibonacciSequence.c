/*
  Program calculate Fibonacci sequence
  using fork(), wait() and child processes
*/
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>

int main()
{
pid_t pid;

	/* fork a child process */
	pid = fork();

	if (pid < 0) { /* error occurred */
		fprintf(stderr, "Fork Failed\n");
		exit(-1);
	}
	else if (pid == 0) { /* child process */
		printf("I am the child %d\n",pid);
        printf("---------------------------------\n");
        printf("Enter the number of Fibonacci Sequence:\n");
        int num;
        scanf("%d", &num);
        printf("---------------------------------\n");
        
        if(num<0)
        {
            printf("Number can't be negative.\nTry Again.\n");
        }
         else if(num==0)
        {

             printf("0");
             printf("\nThe sum of the two numbers before it: %d\n", num);
        }
        else if(num==1)
        {

             printf("0 1");
             printf("\nThe sum of the two numbers before it: %d\n", num);
        }
        else
        {
        int  f[num+2];
        int i;
        f[0]=0;
        f[1]=1;
        printf("0 1");
        for(i=2; i<=num;i++)
        {
            f[i]=f[i-1]+f[i-2];
            printf(" %d", f[i]);
        }
        printf("\nThe sum of the two numbers before it: %d\n", f[num]);
        }
		
	}
	else { /* parent process */
		/* parent will wait for the child to complete */
		printf("I am the parent %d\n",pid);
		wait(NULL);
		
		printf("Child Complete\n");
		exit(0);
	}

}

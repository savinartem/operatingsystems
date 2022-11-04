/**
	pipe line project using C
	parent process and 2 child processes

*/

#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <unistd.h>


int main(int args, char* argv[])
{
    pid_t pid1, pid2;
    int fd, fd1;
    char * myfifo = "fifoFile";//name for fifo file

    /* Child 1 */
    pid1=fork();

    /*Error occured*/
    if (pid1<0)
    {
         // fprintf(stderr, "Fork Failed.");  
          return 1;
    }
    
    else if(pid1==0)
    {
        
        // Creating the FIFO
         mkfifo(myfifo, 0666);//"0666" read and write permision
         printf("Child#1 Openning......\n");
        // Open FIFO for write only
        fd = open(myfifo, O_WRONLY);
        printf("Child#1 Writing......\n");
          /*
          int dup2(int oldfd, int newfd);
          for redirect outputbto the file
           */  
         dup2(fd,1);
         execlp("ls","ls","-F", NULL);
            
        close(fd);
    }
    /* Child 2 */
    pid2=fork();
        /*Error occured*/
    if (pid2<0)
    {
          fprintf(stderr, "Fork Failed.");  
          return 1;
    }
    else if (pid2==0)
    {
        printf("Chil#2 Openning......\n");
        mkfifo(myfifo, 0666);
        printf("Child#2 Reading......\n");
       // Open FIFO for Read only
        fd = open(myfifo, O_RDONLY);
        dup2(fd,0);
        execlp("nl","nl", NULL);
        close(fd1);
    }
    //parent
    //wait for children to finish
    wait(NULL);
    wait(NULL); 
    printf("Done............\n");
    return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int val = 1;

int main()
{
    int pid1 = fork();

    if( pid1!=0 )
    {
    	wait(&val);
        printf("I am the parent: %d\n",getpid());
    }
    else
    {
        int pid2 = fork();
        if( pid2 == 0 )
        	printf("I am the grandchild: %d\n",getpid());
        else {
        	wait(&val);
        	printf("I am the child: %d\n",getpid());
        }
    }
    return(0);
}

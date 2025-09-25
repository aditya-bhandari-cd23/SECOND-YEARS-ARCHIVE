// process sync

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<wait.h>

int main(int argc, char* argv[])
{
    pid_t p = fork();
    int retval = 0;

    if (p < 0)
        printf("Error creating a child process");
    else if (p == 0) {
        printf("Pid of child: %d, pid of parent: %d", getpid(), getppid());
        execl("./binsearch", argv[1], NULL);
    }
    else {
        printf("Pid: %d", getpid());
        wait(&retval);
        if (WIFEXITED(retval))
            printf("Child terminated normally");
        else
            printf("Child terminated abnormally");
    }
}
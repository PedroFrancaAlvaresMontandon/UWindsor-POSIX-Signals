#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    pid_t pid1, pid2;
    int status;
    int child2_exit_status = 17; //exit status

    
    pid1 = fork();

    if (pid1 < 0) {
        fprintf(stderr, "Fork 1 Failed\n");
        exit(1);
    } 
    
    if (pid1 == 0) {
        //child orphan
        printf("1st child created. PID=%d\n", getpid());
        printf("becoming orphan\n");

        //ensures the parent terminates first, make this process an orphan
        sleep(5); 

        printf("1st child, PID=%d, PPID=%d orphaned!\n", getpid(), getppid());
        exit(0);
    }

    //second child process
    pid2 = fork();
    
    if (pid2 < 0) {
        fprintf(stderr, "Fork 2 Failed\n");
        exit(1);
    } 
    
    if (pid2 == 0) {
        //child process 2 
        printf("2nd child created. PID=%d\n", getpid());
        printf("I will be waited for by my parent...\n");
        
        sleep(1); //small delay 
        
        //exiting with a custom status value.
        exit(child2_exit_status); 
    }

    //parent Process (waits)
    
    // waitpid() to wait specifically for the second child.
    waitpid(pid2, &status, 0); 

    //check if the child exited normally
    if (WIFEXITED(status)) {
        
        //extract the child's exit status value.
        int exit_status = WEXITSTATUS(status);
        
        //print the PID and the extracted exit status.
        printf("Parent waited for pid=%d sucessfully. Child exit status was: %d\n", pid2, exit_status);
    } else {
        printf("Parent waited for pid=%d, but it terminated abnormally.\n", pid2);
    }

    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>

//parent custom handler for SIGINT
void parent_sigint_handler(int sig) {
    printf("\n[Parent]: Parent caught SIGINT! (Custom handler).\n");
}

int main() {
    pid_t child_pid;

    //install a handler for (Ctrl+c)
    signal(SIGINT, parent_sigint_handler);
    printf("[Parent]: Installed custom SIGINT handler.\n");

    //ignore (Ctrl+z)
    signal(SIGTSTP, SIG_IGN);
    printf("[Parent]: Set SIGTSTP to be ignored.\n");

    printf("[Parent]: Forking child...\n");
    child_pid = fork();

    if (child_pid < 0) {
        fprintf(stderr, "Fork Failed\n");
        exit(1);
    }

    if (child_pid == 0) {
        //child
        //use execlp to run the 'donothing' program
        printf("   [Child]: I am PID %d, now executing './donothing'...\n", getpid());
        
        execlp("./donothing", "donothing", NULL);

        fprintf(stderr, "   [Child]: EXEC FAILED! Make sure 'donothing' is compiled.\n");
        exit(1);
    } 
    
    //parent process (continues)
    
    printf("[Parent]: Child process (PID %d) is running 'donothing'.\n", child_pid);

    sleep(2);

    //check if Ctrl+z is still ignored
    //send SIGTSTP to the child If it's ignored, the child will continue to run 
    printf("[Parent]: TEST 1: Sending SIGTSTP (Ctrl+Z) to child. Child should ignore it...\n");
    kill(child_pid, SIGTSTP);

    printf("[Parent]: Waiting 2 seconds to see if child is still alive...\n");
    sleep(2);

    //check if handler is set to defaul
    //default handler for SIGINT is to terminate
    printf("[Parent]: TEST 2: Sending SIGINT (Ctrl+C) to child. Child should terminate...\n");
    kill(child_pid, SIGINT);

    int status;
    waitpid(child_pid, &status, 0);

    //check WIFSIGNALED. If true, it means them child was terminated by a signal.
    if (WIFSIGNALED(status)) {
        if (WTERMSIG(status) == SIGINT) {
            printf("[Parent]: SUCCESS. Child was terminated by SIGINT, as expected.\n");
        } else {
            printf("[Parent]: FAILED. Child was terminated by a different signal.\n");
        }
    } else {
        printf("[Parent]: FAILED. Child exited normally, but should have been killed by SIGINT.\n");
    }

    printf("[Parent]: Tests complete. Exiting.\n");
    return 0;
}
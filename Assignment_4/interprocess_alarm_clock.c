#include <stdio.h>
#include <stdlib.h>     
#include <unistd.h>     
#include <signal.h>    
#include <sys/wait.h>   

void alarm_handler(int sig) {
    printf("Ding!\n");
}

int main(int argc, char *argv[]) {
    
    pid_t pid;
    int seconds;

    //the number of seconds must be a command line argument
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <seconds>\n", argv[0]);
        exit(1);
    }

    //convert the argument from a string to an integer
    seconds = atoi(argv[1]);
    if (seconds <= 0) {
        fprintf(stderr, "Seconds must be a positive number.\n");
        exit(1);
    }

    //parent installs the SIGALRM handler 
    signal(SIGALRM, alarm_handler);

    pid = fork();

    if (pid < 0) {
        fprintf(stderr, "Fork Failed\n");
        exit(1);
    }

    if (pid == 0) {
        //child process

        //child sleeps for the number of seconds from the command line argument
        sleep(seconds);

        //after sleeping the child sends the SIGALRM signal to its parent process
        kill(getppid(), SIGALRM);
        
        exit(0); 
    } else {
        //parent process
        
        printf("Alarm application running waiting for alarm to go off\n");

        //the parent process pauses its execution. It will only wake up when a signal is delivered
        pause();

        //once the handler finishes, pause() returns, and the code continues
        printf("Done!\n");

        //clean up the zombie process
        wait(NULL);
    }

    return 0;
}
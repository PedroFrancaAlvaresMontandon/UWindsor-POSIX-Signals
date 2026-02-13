#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

void signal_handler(int signum) {
    
    //print out the signal number to identify which signal was caught.
    if (signum == SIGINT) {
        printf("\nCaught signal %d (SIGINT - Ctrl+C)\n", signum);
    } else if (signum == SIGQUIT) {
        printf("\nCaught signal %d (SIGQUIT - Ctrl+\\)\n", signum);
    } else {
        printf("\nCaught unexpected signal: %d\n", signum);
    }
}

int main() {
    
    //install the same handler for both SIGINT
    if (signal(SIGINT, signal_handler) == SIG_ERR) {
        fprintf(stderr, "Could not install handler for SIGINT\n");
        exit(1);
    }
    
    //and SIGQUIT.
    if (signal(SIGQUIT, signal_handler) == SIG_ERR) {
        fprintf(stderr, "Could not install handler for SIGQUIT\n");
        exit(1);
    }

    printf("Signal handler installed for SIGINT (Ctrl+C) and SIGQUIT (Ctrl+\\).\n");
    printf("PID: %d. Send signals to this process (or press keys) to test.\n", getpid());
    printf("Press Ctrl+C to send SIGINT.\n");
    printf("Press Ctrl+\\ to send SIGQUIT.\n");
    printf("Press Ctrl+Z to stop the process (if you need to).\n");

    //infinite loop with pause() keeps the program alive, waiting for signals
    while (1) {
        pause(); //wait for a signal to arrive
    }

    return 0; 
}
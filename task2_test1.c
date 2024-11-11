// task2_test1.c
#include "types.h"
#include "stat.h"
#include "user.h"

int main() {
    // Run primeproc with argument 3 in the background
    printf(1, "Running 'primeproc 3 &' in the background\n");
    if (fork() == 0) { // Child process to execute primeproc
        char *args[] = {"primeproc", "3", 0};
        exec("primeproc", args);
        exit();
    }

    // Add a slight delay to ensure primeproc has time to start
    int start_ticks = uptime();
    while (uptime() - start_ticks < 100);

    // Run the ps command to display process status
    printf(1, "\nRunning 'ps' to display process statuses\n");
    if (fork() == 0) { // Child process to execute ps
        char *args[] = {"ps", 0};
        exec("ps", args);
        exit();
    }
    
    // Wait for all child processes to finish
    wait();
    exit();
}

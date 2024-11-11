// task2_test2.c
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
    sleep(5);

    // Run the nice command to set priority for PID 3 to 6
    printf(1, "\nRunning 'nice 6 3'\n");
    if (fork() == 0) { // Child process to execute nice
        char *args[] = {"nice", "6", "3", 0};
        exec("nice", args);
        exit();
    }
    wait(); // Wait for the nice command to complete

    // Run the ps command to display process status
    printf(1, "\nRunning 'ps' to display process statuses\n");
    if (fork() == 0) { // Child process to execute ps
        char *args[] = {"ps", 0};
        exec("ps", args);
        exit();
    }
    wait(); // Wait for the ps command to complete

    // Wait for all child processes to finish
    wait();

    exit();
}

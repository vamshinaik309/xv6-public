// task2_test3.c
#include "types.h"
#include "stat.h"
#include "user.h"

#define TICKS_PER_SECOND 100 // Adjust according to xv6 configuration

int main() {
    // Step 1: Run 'primeproc 3 &' in the background
    printf(1, "Running 'primeproc 3 &' in the background\n");
    if (fork() == 0) { // Child process to execute primeproc
        char *args[] = {"primeproc", "3", 0};
        exec("primeproc", args);
        printf(1, "Error: exec primeproc failed\n");
        exit();
    }

    // Step 2: Busy-wait loop to ensure primeproc has started and its child processes are running
    int start_ticks = uptime();
    while (uptime() - start_ticks < 2 * TICKS_PER_SECOND); // Wait for approximately 2 seconds

    // Step 3: Run 'nice 7 3' to set priority for PID 3
    printf(1, "\nRunning 'nice 7 3'\n");
    if (fork() == 0) { // Child process to execute nice
        char *args[] = {"nice", "7", "3", 0};
        exec("nice", args);
        printf(1, "Error: exec nice failed\n");
        exit();
    }

    // Step 4: Wait for child processes to finish
    wait(); // Wait for the first fork (primeproc)
    wait(); // Wait for the second fork (nice)

    exit();
}

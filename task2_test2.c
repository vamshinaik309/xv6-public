// task2_test2.c
#include "types.h"
#include "stat.h"
#include "user.h"

#define TICKS_PER_SECOND 100 // Assuming 100 ticks per second in xv6

int main() {
    // Run primeproc with argument 3 in the background
    printf(1, "Running 'primeproc 3 &' in the background\n");
    if (fork() == 0) { // Child process to execute primeproc
        char *args[] = {"primeproc", "3", 0};
        exec("primeproc", args);
        exit();
    }

    // Busy-wait for 2 seconds (approx 200 ticks)
    // int start_ticks = uptime(); // Get current uptime in ticks
    // while (uptime() - start_ticks < 2 * TICKS_PER_SECOND); // Wait until 2 seconds have passed
    // sleep(5);
    int ii=0;
    int x=0;
    for (ii=0;ii<=4000000000;ii++){
        x=x+3.46;
    }
    // Run the nice command to set priority for PID 3 to 6
    printf(1, "\nRunning 'nice 6 3'\n");
    if (fork() == 0) { // Child process to execute nice
        char *args[] = {"nice", "6", "3", 0};
        exec("nice", args);
        exit();
    }
    wait(); // Wait for the nice command to complete

    exit();
}


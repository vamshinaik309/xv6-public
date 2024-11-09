#include "types.h"
#include "stat.h"
#include "user.h"

int main(void) {
    int pid = getpid();

    // Fork a new process
    if (fork() == 0) {
        printf(1, "Loop1 PID: %d\n", pid);

        // This is the child process: the infinite loop
        while (1) {
            // printf(1, "Loop1 PID: %d\n", pid);
            sleep(100); // Slow down the output
        }
    }

    // Parent process exits immediately
    exit();
}

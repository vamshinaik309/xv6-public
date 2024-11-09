// test1.c
#include "types.h"
#include "stat.h"
#include "user.h"

int main() {
    // int pid = getpid();  // Get the current process ID

    // Test 1: Set priority for the current process within the valid range
    printf(1, "nice 10\n");
    if (fork() == 0) {  // Run nice as a child process
        char *args[] = {"nice", "10", 0};
        exec("nice", args);
        exit();
    }
    wait();

    // Test 2: Set an invalid negative priority for the current process (should fail)
    printf(1, "nice -5\n");
    if (fork() == 0) {
        char *args[] = {"nice", "-5", 0};
        exec("nice", args);
        exit();
    }
    wait();

    // Test 3: Set priority for a specified PID (e.g., 1) within the valid range
    printf(1, "nice 1 5\n");
    if (fork() == 0) {
        char *args[] = {"nice", "1", "5", 0};
        exec("nice", args);
        exit();
    }
    wait();

    exit();
}

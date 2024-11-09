// test2.c
#include "types.h"
#include "stat.h"
#include "user.h"

int main() {
    // Test 1: Pass a non-numeric string as priority (should fail)
    printf(1, "nice abc\n");
    if (fork() == 0) {
        char *args[] = {"nice", "abc", 0};
        exec("nice", args);
        exit();
    }
    wait();

    // Test 2: Set a priority above the allowed range (e.g., 30)
    printf(1, "nice 30\n");
    if (fork() == 0) {
        char *args[] = {"nice", "30", 0};
        exec("nice", args);
        exit();
    }
    wait();

    // Test 3: Use an invalid PID with a valid priority
    printf(1, "nice 9999 5\n");
    if (fork() == 0) {
        char *args[] = {"nice", "9999", "5", 0};
        exec("nice", args);
        exit();
    }
    wait();

    exit();
}

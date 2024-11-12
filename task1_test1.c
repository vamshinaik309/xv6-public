// test1.c
#include "types.h"
#include "stat.h"
#include "user.h"

int main() {

    printf(1, "Running test1.c tests for nice CLI calls\n");

    // Test 1: Set a priority out of range (9) for current process
    printf(1, "nice 9\n");
    if (fork() == 0) {
        char *args[] = {"nice", "9", 0};
        exec("nice", args);
        exit();
    }
    wait();

    // Test 2: Set priority 0 (invalid, out of range)
    printf(1, "nice 0\n");
    if (fork() == 0) {
        char *args[] = {"nice", "0", 0};
        exec("nice", args);
        exit();
    }
    wait();

    // Test 3: Set a negative priority (-9) for the current process (should fail)
    printf(1, "nice -9\n");
    if (fork() == 0) {
        char *args[] = {"nice", "-9", 0};
        exec("nice", args);
        exit();
    }
    wait();

    // Test 4: Set valid priority (1) for the current process
    printf(1, "nice 1\n");
    if (fork() == 0) {
        char *args[] = {"nice", "1", 0};
        exec("nice", args);
        exit();
    }
    wait();

    // Test 5: Set another valid priority (5) for the current process
    printf(1, "nice 5\n");
    if (fork() == 0) {
        char *args[] = {"nice", "5", 0};
        exec("nice", args);
        exit();
    }
    wait();

    // Test 6: Invalid argument (non-numeric value)
    printf(1, "nice ,\n");
    if (fork() == 0) {
        char *args[] = {"nice", ",", 0};
        exec("nice", args);
        exit();
    }
    wait();

    // Test 7: Set priority for a specific PID (1) with invalid value (9)
    printf(1, "nice 1 9\n");
    if (fork() == 0) {
        char *args[] = {"nice", "1", "9", 0};
        exec("nice", args);
        exit();
    }
    wait();

    // Test 8: Set priority for a specific PID (1) with valid priority (5)
    printf(1, "nice 1 5\n");
    if (fork() == 0) {
        char *args[] = {"nice", "1", "5", 0};
        exec("nice", args);
        exit();
    }
    wait();

    // Test 9: Set priority for a specific PID (1) with a non-numeric priority (abc)
    printf(1, "nice 1 abc\n");
    if (fork() == 0) {
        char *args[] = {"nice", "1", "abc", 0};
        exec("nice", args);
        exit();
    }
    wait();

    // Test 10: Set priority for a specific PID (4) with valid priority (5) - PID might not exist
    printf(1, "nice 40 5\n");
    if (fork() == 0) {
        char *args[] = {"nice", "40", "5", 0};
        exec("nice", args);
        exit();
    }
    wait();

    exit();
}

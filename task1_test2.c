#include "types.h"
#include "stat.h"
#include "user.h"

int main() {
    int pid = getpid();  // Current process PID

    printf(1, "Running comprehensive tests for nice system call\n");

    // Test 1: Set priority for the current process (valid range)
    int old_priority = chpr(pid, 4);
    if (old_priority >= 0) {
        printf(1, "Test 1 Passed: PID %d, Old Priority %d, New Priority 4\n", pid, old_priority);
    } else {
        printf(1, "Test 1 Failed: Unable to change priority for current process to priority 4\n");
    }

    // Test 2: Set out-of-range priority (25) for the current process
    old_priority = chpr(pid, 25);
    if (old_priority == -1) {
        printf(1, "Test 2 Passed: Out-of-range priority (25) correctly rejected\n");
    } else {
        printf(1, "Test 2 Failed: Out-of-range priority not handled\n");
    }

    // Test 3: Set negative priority (-5) for the current process
    old_priority = chpr(pid, -5);
    if (old_priority == -1) {
        printf(1, "Test 3 Passed: Negative priority (-5) correctly rejected\n");
    } else {
        printf(1, "Test 3 Failed: Negative priority not handled\n");
    }

    // Test 4: Set maximum valid priority (5) for the current process
    old_priority = chpr(pid, 5);
    if (old_priority >= 0) {
        printf(1, "Test 4 Passed: PID %d, Old Priority %d, New Priority 5\n", pid, old_priority);
    } else {
        printf(1, "Test 4 Failed: Unable to change priority to maximum valid value 5\n");
    }

    // Test 5: Set minimum valid priority (1) for the current process
    old_priority = chpr(pid, 1);
    if (old_priority >= 0) {
        printf(1, "Test 5 Passed: PID %d, Old Priority %d, New Priority 1\n", pid, old_priority);
    } else {
        printf(1, "Test 5 Failed: Unable to change priority to minimum valid value 1\n");
    }


    printf(1, "All tests completed\n");
    exit();
}
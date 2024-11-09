// #include "types.h"
// #include "stat.h"
// #include "user.h"
// #include "fcntl.h"

// int main(int argc, char *argv[]) {
//     int priority, pid;

//     // If one argument is passed, assume it's the new priority for the current process
//     if (argc == 2) {
//         pid = getpid();  // Get the PID of the current process
//         priority = atoi(argv[1]);
//         printf(1, "Setting priority of current process (PID: %d) to %d\n", pid, priority);    
//         sleep(2000);    
//     } 
//     // If two arguments are passed, the first is the PID, and the second is the priority
//     else if (argc == 3) {
//         pid = atoi(argv[1]);
//         priority = atoi(argv[2]);
//     } 
//     else {
//         // Print usage message if incorrect number of arguments
//         printf(2, "Usage: nice pid priority\n");
//         exit();
//     }

//     // Check if the priority is within the valid range
//     if (priority < 0 || priority > 20) {
//         printf(2, "Invalid priority (0-20)!\n");
//         exit();
//     }

//     // Call the system call to change the nice value
//     chpr(pid, priority);
//     exit();
// }

#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"

int parse_priority(const char *str) {
    int priority = 0;
    int i = 0;

    // Ensure the input is a positive number (no negative sign allowed)
    while (str[i] != '\0') {
        if (str[i] < '0' || str[i] > '9') {
            return -1;  // Return -1 if any non-numeric character is found
        }
        priority = priority * 10 + (str[i] - '0');
        i++;
    }

    // Check if the priority is within the valid range (0-20)
    if (priority < 0 || priority > 20) {
        return -1;  // Return -1 if the priority is out of bounds
    }

    return priority;
}

int main(int argc, char *argv[]) {
    int priority, pid, old_priority;

    // If one argument is passed, assume it's the new priority for the current process
    if (argc == 2) {
        pid = getpid();  // Get the PID of the current process
        priority = parse_priority(argv[1]);
        if (priority == -1) {
            printf(2, "Invalid priority (0-20)!\n");
            exit();
        }
    } 
    // If two arguments are passed, the first is the PID, and the second is the priority
    else if (argc == 3) {
        pid = atoi(argv[1]);
        priority = parse_priority(argv[2]);
        if (priority == -1) {
            printf(2, "Invalid priority it should be in range (0-20)!\n");
            exit();
        }
    } 
    else {
        // Print usage message if incorrect number of arguments
        printf(2, "Usage: nice [pid] priority\n");
        exit();
    }

    // Check if the priority is within the valid range
    if (priority < 0 || priority > 20) {
        printf(2, "Invalid priority (0-20)!\n");
        exit();
    }

    // Call the system call to change the nice value and get the old priority
    old_priority = chpr(pid, priority);
    
    if (old_priority == -1) {
        printf(2, "Failed to set priority for PID %d\n", pid);
    } else {
        // Print PID and old priority in the desired format
        printf(1, "%d %d\n", pid, old_priority);
    }

    exit();
}

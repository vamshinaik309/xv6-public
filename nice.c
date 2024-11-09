#include "types.h"
#include "stat.h"
#include "user.h"

int 
main(int argc, char *argv[]) {
    int pid, value, old_value;

    if (argc == 3) {  // Case: nice <pid> <value>
        pid = atoi(argv[1]);
        value = atoi(argv[2]);
        old_value = nice(pid, value);
    } else if (argc == 2) {  // Case: nice <value>
        pid = getpid();  // Set pid to the current process ID
        value = atoi(argv[1]);
        old_value = nice(pid, value);
    } else {
        printf(2, "Usage: nice <pid> <value> or nice <value>\n");
        exit();
    }

    if (old_value >= 0)
        printf(1, "%d %d\n", pid, old_value);  // Print the PID and old nice value
    else
        printf(2, "Error: Invalid arguments or process not found\n");

    exit();
}
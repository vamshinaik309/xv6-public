// primeproc.c
#include "types.h"
#include "stat.h"
#include "user.h"

int mutexid;

void wait_for_seconds(int seconds) {
    int start_ticks = uptime();
    while (uptime() - start_ticks < seconds * 100) {
    }
}

int is_prime(int num) {
    if (num <= 1) return 0;
    for(int i = 2; i <= num / 2; i++) {
        if(num % i == 0){
            return 0;
        }
    }
    return 1;
}

void calculate_primes(int limit, int mutexid) {
    int num = 2;
    int count = 0;

    while(count < limit) {
        if(is_prime(num)) {
            lock(mutexid);
            printf(1, "PID %d printing %d th Prime number:%d\n", getpid(), count + 1, num);
            unlock(mutexid);

            count++;
            wait_for_seconds(1);
        }
        num++;
    }
}

int main(int argc, char *argv[]) {
    int n = 1;
    int pipe_fd = -1;

    if(argc > 1)
        n = atoi(argv[1]);

    if (argc > 2)
        pipe_fd = atoi(argv[2]); // Get the write end of the pipe from the arguments

    if (n < 1)
        n = 1;

    int k, pid;

    mutexid = getmutex();
    if(mutexid < 0){
        printf(1, "Error: Unable to get mutex\n");
        exit();
    }

    for(k = 0; k < n; k++) {
        pid = fork();
        if(pid < 0) {
            printf(1, "Error: fork failed\n");
            exit();
        } else if(pid == 0) {
            printf(1, "Child %d started\n", getpid());
            calculate_primes(1000, mutexid);
            printf(1, "Child %d finished\n", getpid());
            exit();
        } else {
            printf(1, "Parent %d created child %d\n", getpid(), pid);
        }
    }

    // Signal that all child processes have been created
    if(pipe_fd >= 0) {
        write(pipe_fd, "done", 4);
        close(pipe_fd); // Close the write end after signaling
    }

    for(k = 0; k < n; k++) {
        wait();
    }

    exit();
}

// primeproc.c
#include "types.h"
#include "stat.h"
#include "user.h"

int
is_prime(int num)
{
    if (num <= 1) return 0;
    for(int i = 2; i <= num / 2; i++){
        if(num % i == 0){
            return 0;
        }
    }
    return 1;
}

void delay_seconds(int seconds) {
    int start_ticks = uptime();
    while (uptime() - start_ticks < seconds * 100); // Assuming 100 ticks per second
}

void
calculate_primes(int limit)
{
    int num = 2; // Starting number to check for primality
    int count = 0; // Number of primes found

    while(count < limit) {
        if(is_prime(num)) {
            // Print the prime number
            // printf(1, "PID %d: %d\n", getpid(), num);
            printf(1, "PID %d: Prime #%d: %d\n", getpid(), count + 1, num);
            count++;

            // Sleep to prevent output overflow
            delay_seconds(1);
            sleep(1);
        }
        num++; // Move to the next number
    }
}

int
main(int argc, char *argv[])
{
    int n = 1; // Default number of child processes

    if(argc > 1)
        n = atoi(argv[1]);

    if (n < 1)
        n = 1;

    int k, pid;

    for(k = 0; k < n; k++) {
        pid = fork();
        if(pid < 0) {
            printf(1, "Error: fork failed\n");
            exit();
        } else if(pid == 0) {
            // Child process
            printf(1, "Child %d started\n", getpid());
            calculate_primes(1000); // Adjust the limit as needed
            printf(1, "Child %d finished\n", getpid());
            exit();
        } else {
            // Parent process
            printf(1, "Parent %d created child %d\n", getpid(), pid);
            // Optionally, you can remove the wait() here to have all children run concurrently
        }
    }

    // Parent waits for all child processes to finish
    for(k = 0; k < n; k++) {
        wait();
    }

    exit();
}

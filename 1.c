#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
int main(int argc, char *argv[]) {
// Check for valid input
if (argc != 2) {
printf("Usage: %s <starting_number>\n", argv[0]);
exit(1);
}
// Convert input to integer
int n = atoi(argv[1]);
if (n <= 0) {
printf("Error: Starting number must be positive\n");
exit(1);
}
// Create a child process
pid_t child_pid = fork();
if (child_pid == -1) {
perror("fork");
exit(1);
}
// Child process generates the Collatz sequence
if (child_pid == 0) {
while (n != 1) {
printf("%d\n", n);
if (n % 2 == 0) {
n /= 2;
} else {
n = 3 * n + 1;
}
}
printf("%d\n", n);
exit(0);
}
// Parent process waits for child to finish
wait(NULL);
printf("Child process generated the Collatz sequence for %d\n", n);
return 0;
}


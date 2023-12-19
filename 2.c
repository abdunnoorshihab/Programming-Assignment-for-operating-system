#include <sys/ipc.h> #include <stdio.h> #include <stdlib.h> #include <sys/types.h> #include <sys/wait.h> #include <unistd.h>
int main() {
int n = 3;
int fd[2 * n]; // array to store file descriptors of pipes
char write_msg[n][100]; // array to store messages to be written by child processes
char read_msg[100]; // array to store messages to be read by parent process int pid; // variable to store process id
// Create pipes
for (int i = 0; i < n; i++) {
if (pipe(&fd[2 * i]) == -1) { // create a pipe and store the file descriptors in the fd array
printf("Error! Cannot create pipe\n"); return -1;
}
}
// Fork child processes
for (int i = 0; i < n; i++) {
if ((pid = fork()) == 0) { // fork a child process
printf("Child %d (pid %d) writing to parent (pid %d)...\n", i, getpid(),
getppid());
close(fd[2 * i]); // close read end of the pipe in the child process
int j = 0;
int counter = 0;
char prev_in = '\0'; // Variable to store the previous value of 'in' while (1) {
char in; scanf("%c", &in);
if (in == '\n' && prev_in == '\n') { // As input is taken character by character this checks if the current AND previous character is also a new line
counter++;
if (counter == 2) { break;
}
}
else {
// Store the previous value of 'in'
character
char prev_char = prev_in;
prev_in = in; // Update the previous value with the current 'in'
counter = 0; // if its a non newline character reset the counter
to 0
write_msg[i][j] = in; // read input character by character and store it in write_msg array
j++;
}
}
write_msg[i][j] = '\0'; // null terminate the message
write(fd[2 * i + 1], &write_msg[i], sizeof(write_msg[i])); // write the message to the parent process through the pipe
close(fd[2 * i + 1]); // close write end of the pipe in the child
process
}
exit(0); // exit the child process
else { // parent process
wait(&pid); // wait for child process to finish
}
}
// Read from child processes for (int i = 0; i < n; i++) {
read(fd[2 * i], read_msg, sizeof(read_msg)); // read the message from the child process through the pipe
close(fd[2 * i]); // close read end of the pipe in the parent process printf("\nParent (pid %d) reading from child process %d (pid %d): %s",
getpid(), i, pid, read_msg); // print the message received from the child process
}
printf("\n");
}


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    pid_t pid;

    pid = fork();
    if (pid < 0) {
        perror("Fork failed");
        return 1;
    }
    else if (pid == 0) {
        printf("Child process (PID = %d) is executing\n", getpid());
        execlp("ls", "ls", "-l", NULL);

        perror("execlp failed");
        exit(EXIT_FAILURE);
    }
    else {
        printf("Parent process (PID = %d) is waiting for child to finish\n", getpid());

        wait(NULL);

        printf("Parent process finished\n");
    }

    return 0;
}





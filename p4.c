#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#define FIFO_NAME "myfifo"
void writerProcess()
{
    int fd;

    mkfifo(FIFO_NAME, 0666);

    fd = open(FIFO_NAME, O_WRONLY);

    char message[] = "Hello, Reader!";
    write(fd, message, sizeof(message));

    close(fd);

    unlink(FIFO_NAME);
}
void readerProcess()
{
    int fd;
    char buffer[100];

    fd = open(FIFO_NAME, O_RDONLY);

    read(fd, buffer, sizeof(buffer));

    printf("Reader received: %s\n", buffer);

    close(fd);
}
int main()
{

    pid_t pid = fork();
    if (pid < 0)
    {
        fprintf(stderr, "Fork failed\n");
        return 1;
    }
    else if (pid > 0)
    {

        writerProcess();
    }
    else
    {

        readerProcess();
    }
    return 0;
}

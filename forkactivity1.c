#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
void forkexample()
{
    // child process because return value zero
    if (fork() == 0)
    {
        printf("Hello from Child!\n");
        sleep(1);
        printf("Hello from Child!\n");
        sleep(1);
        printf("Hello from Child!\n");
        sleep(1);
        printf("Hello from Child!\n");
        sleep(1);
        printf("Hello from Child!\n");
        sleep(1);
        printf("Hello from Child!\n");
        sleep(1);
        printf("Hello from Child!\n");
        sleep(1);
        printf("Hello from Child!\n");
        sleep(1);
        printf("Hello from Child!\n");
        sleep(1);
        printf("Hello from Child!\n");
        sleep(1);
      }
    // parent process because return value non-zero.
    else
        printf("Hello from Parent!\n");
        sleep(2);
        printf("Hello from Parent!\n");
        sleep(2);
        printf("Hello from Parent!\n");
        sleep(2);
        printf("Hello from Parent!\n");
        sleep(2);
        printf("Hello from Parent!\n");
        sleep(2);
        printf("Hello from Parent!\n");
        sleep(2);
        printf("Hello from Parent!\n");
        sleep(2);
        printf("Hello from Parent!\n");
        sleep(2);
        printf("Hello from Parent!\n");
        sleep(2);
        printf("Hello from Parent!\n");
        sleep(2);
}
int main()
{
    forkexample();
    exit(0);
}

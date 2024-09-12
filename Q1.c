#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <time.h>

int main()
{
    pid_t pid;
    int i;

    srand(time(NULL));

    // 7 children
    for (i = 0; i < 7; i++)
    {
        pid = fork();

        if (pid < 0)
        {
            // Fork failed
            perror("Fork failed");
            exit(1);
        }
        else if (pid == 0)
        {
            // Child process
            int sum = 0;
            int random_number;

            // Generating random numbers
            for (int j = 0; j < 4; j++)
            {
                random_number = (rand() % 100) + 1;
                random_number = (random_number * getpid()) % 100 + 1;
                sum += random_number;
            }

            // Mean
            int mean = sum / 4;
            printf("Mean of random numbers by child %d of(PID: %d): %d\n", i + 1, getpid(), mean);
            exit(0);
        }
    }

    // Parent waiting for child to finish
    for (i = 0; i < 7; i++)
    {
        wait(NULL);
    }

    return 0;
}

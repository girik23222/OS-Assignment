#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

void program(const char *program, char *const argv[]) {
    pid_t pid = fork();
    if (pid == -1) {
        perror("fork");
        exit(1);
    }
    
    if (pid == 0) {
       
        execv(program, argv);
        // If execv returns, there was an error
        perror("execv");
        exit(1);
    }
}

int main() {

    char *date_args[] = {"./date_formats", "-r", NULL};

    char *calendar_args[] = {"./calendar", "9", "2024", NULL};

    char *uptime_args[] = {"./uptime", NULL};

    program("./date", date_args);
    program("./cal", calendar_args);
    program("./uptime", uptime_args);

    // Wait for all childs
    for (int i = 0; i < 3; i++) {
        int status;
        wait(&status);
    }

    return 0;
}

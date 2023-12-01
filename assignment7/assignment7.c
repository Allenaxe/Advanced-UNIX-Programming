#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int main() {
    char buf[50];
    pid_t child_pid = fork();

    if (child_pid < 0) {
        perror("Fork failed");
        exit(EXIT_FAILURE);
    }

    if (child_pid == 0) {
        if (setsid() == -1) {
            perror("setsid failed");
            exit(EXIT_FAILURE);
        }
        sprintf(buf, "ps -o pid,pgid,tpgid -p %d", getpid());
        system(buf);
    } else exit(0);

    return 0;
}

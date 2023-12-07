#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define PATH_MAX 512

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <path>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    char buffer[1024] = "\0";

    sprintf(buffer, "find %s -type l -exec ls -la {} \\;", argv[1]);

    system(buffer);

    return 0;
}

#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>

#define BUFFERMAX 4096

int main(int argc, char **argv) {
    char *source = argv[1];
    char *dest = argv[2];
    int rfd = open(source, O_RDONLY);
    int wfd = creat(dest, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH);
    int n = 0;
    char buffer[BUFFERMAX];
    while((n = read(rfd, buffer, BUFFERMAX)) > 0) {
        write(wfd, buffer, n);
    } 
    close(rfd);
    close(wfd);
}
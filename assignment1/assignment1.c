#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

int main()
{
    int offset = 0;
    int fd = open("sample.txt", O_RDWR);
    char rbuffer[30];
    char target[] = "student.";
    while(read(fd, rbuffer, strlen(target))) {
        if(!strcmp(rbuffer, target)) break;
        lseek(fd, offset++, SEEK_SET);
    }
    printf("%s\n", rbuffer);
    lseek(fd, offset - 1, SEEK_SET);
    char wbuffer[] = "NTHU student.\n";
    write(fd, wbuffer, strlen(wbuffer));
    int flen = lseek(fd, 0, SEEK_END);
    lseek(fd, 0, SEEK_SET);
    read(fd, rbuffer, flen);
    printf("%s", rbuffer);
    close(fd);
}
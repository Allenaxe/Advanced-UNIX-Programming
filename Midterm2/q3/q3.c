#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <sys/stat.h>
#include <stdlib.h>

int main(){
    time_t t = time(0);
    struct tm tm1;
    char buffer[256];

    localtime_r(&t, &tm1);
    strftime(buffer, sizeof(buffer), "%X, %A %B %d, %G\n", &tm1);
    printf("%s\n", buffer);

    return 0;
}
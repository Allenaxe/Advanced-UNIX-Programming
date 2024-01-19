#include<stdio.h>
#include<stdlib.h>
#include<sys/time.h>
#include<sys/select.h>
#define DENOMINATOR 1000000

void sleep_us(long long desiredSleepTime){
    struct timeval sleepTime;
    sleepTime.tv_sec = desiredSleepTime / DENOMINATOR;
    sleepTime.tv_usec = desiredSleepTime % DENOMINATOR;

    select(0, NULL, NULL, NULL, &sleepTime);
}

int main(int argc, char *argv[]){
    struct timeval before;
    struct timeval after;
    long long result;
    long long desiredSleepTime = atoll(argv[1]);
    gettimeofday(&before,NULL);
    sleep_us(desiredSleepTime);
    gettimeofday(&after,NULL);
    result = DENOMINATOR * (after.tv_sec - before.tv_sec) + after.tv_usec - before.tv_usec;
    printf("Sleep time: %lld us\n",result);
    return 0;
}
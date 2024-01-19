#include <stdio.h>
#include <signal.h>
#include <unistd.h>

void alarmHandler(int signum) {
    printf("Alarm!\n");
    alarm(0); 
}
void setAlarm(int sec){
    alarm(sec);
    signal(SIGALRM, alarmHandler);
}
void clearAlarm(){
    alarm(0);
}

int main (void) {
    setAlarm(2); //set 2 sec alarm at 0s, will finish at 2s after execution
    sleep(1);
    setAlarm(6); //set 6 sec alarm at 1s, will finish at 7s after execution
    sleep(1);
    setAlarm(3); //set 3 sec alarm at 2s, will finish at 5s after execution
    sleep(4);
    clearAlarm(); //clear all alarms at 6s after execution
}
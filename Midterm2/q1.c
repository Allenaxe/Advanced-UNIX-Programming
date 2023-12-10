#include <stdio.h>
#include <sys/time.h>
#include <time.h>
#include <unistd.h>
#include <sys/stat.h>
#include <stdlib.h>

int main()
{
  int count = 0;
  struct tm tm1;

  while(1) {
    if(count == 6){
      time_t t = time(NULL);
      localtime_r(&t, &tm1);
      printf("%d\n", tm1.tm_sec);
      count = 0;
    }
    sleep(10);
    count++;
  }
}

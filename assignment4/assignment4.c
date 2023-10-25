#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <sys/stat.h>
#include <stdlib.h>

int main()
{
  time_t t = time(0);
  struct tm tm;
  char buf[256];
  setenv("TZ", ":Asia/Taipei", 1); tzset();
  localtime_r(&t, &tm);
  strftime(buf, sizeof(buf), "%a %b %d %X %Z %G", &tm);
  printf("%s\n", buf);
  setenv("TZ", ":Pacific/Auckland", 1); tzset();
  localtime_r(&t, &tm);
  strftime(buf, sizeof(buf), "%a %b %d %X %Z %G", &tm);
  printf("%s\n", buf);
}
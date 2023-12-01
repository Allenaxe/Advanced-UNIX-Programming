#include <stdio.h>
#include <stdlib.h> 
#include <sys/types.h> 
#include <unistd.h>

int main()
{
  pid_t pid = fork();

  if(pid > 0) {
    printf("process %d/%d\n", getpid(), pid);
    sleep(5);
    system("ps aux | grep assignment6");
  }

  else exit(0);

  return 0;
}
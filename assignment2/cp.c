#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <string.h>
#include <fcntl.h>

#define BUFFERMAX 4096

int is_regular_file(const char *path)
{
    struct stat path_stat;
    stat(path, &path_stat);
    return S_ISREG(path_stat.st_mode);
}

int isDirectory(const char *path) {
   struct stat statbuf;
   if (stat(path, &statbuf) != 0)
       return 0;
   return S_ISDIR(statbuf.st_mode);
}

int main(int argc, char **argv) {
    int normalcp = 1;
    for(int i = 1; i < argc; ++i) {
      normalcp &= is_regular_file(argv[i]);
    }

    if(normalcp && argc <= 3) {
      int rfd = open(argv[1], O_RDONLY);
      int wfd = creat(argv[2], S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH);
      int n = 0;
      char buffer[BUFFERMAX];
      while((n = read(rfd, buffer, BUFFERMAX)) > 0) {
          write(wfd, buffer, n);
      } 
      close(rfd);
      close(wfd);
    }

    else {
      char *directory = argv[argc - 1];
      int dir = mkdir(directory, S_IRUSR | S_IWUSR | S_IXUSR | S_IRGRP | S_IWGRP | S_IXGRP | S_IROTH);
      if(!isDirectory(directory)) {
        printf("Failed!\n");
        return 0;
      }
      for(int i = 1; i < argc - 1; ++i) {
        char path[100];
        sprintf(path, "%s/%s", directory, argv[i]);
        int rfd = open(argv[i], O_RDONLY);
        int wfd = creat(path, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH);
        int n = 0;
        char buffer[BUFFERMAX];
        while((n = read(rfd, buffer, BUFFERMAX)) > 0) {
          write(wfd, buffer, n);
        } 
        close(rfd);
        close(wfd);
      }
    }
}
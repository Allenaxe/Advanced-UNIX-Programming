#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <getopt.h>
#include <strings.h>
#define MAXSIZE 20
#define COUNT 1
#define UNIQUE 2
#define IGNORE 4

int main(int argc, char **argv)
{
  int opt = -1;
  int flags = 0;
  static struct option long_options[] = {
    {"count", 2, NULL, 'c'},
    {"unique", 2, NULL, 'u'},
    {"ignore-case", 2, NULL, 'i'},
  };
  while((opt = getopt_long(argc, argv, "c::i::u::", long_options, NULL)) != -1)  {
    switch(opt) {
      case 'c':
        //printf("count flag\n");
        flags |= COUNT;
        break;
      case 'u':
        //printf("unique flag\n");
        flags |= UNIQUE;
        break;
      case 'i':
        //printf("ignore flag\n");
        flags |= IGNORE;
        break;
    }
  }
  if(flags == COUNT) {
    FILE *file = fopen(argv[argc - 1], "r");
    int count = 1;
    char buffer[MAXSIZE], previos[MAXSIZE];
    fgets(previos, MAXSIZE, file);
    previos[strcspn(previos, "\n")] = '\0';
    while(fgets(buffer, MAXSIZE, file) != NULL) {
      buffer[strcspn(buffer, "\n")] = '\0';
      if(!strcmp(buffer, previos)) {
        ++count;
      }
      else {
        printf("      %d %s\n", count, previos);
        strcpy(previos, buffer);
        count = 1;
      }
    }
    printf("      %d %s\n", count, previos);
    fclose(file);
  }

  if(flags == UNIQUE) {
    FILE *file = fopen(argv[argc - 1], "r");
    int count = 1;
    char buffer[MAXSIZE], previos[MAXSIZE];
    fgets(previos, MAXSIZE, file);
    previos[strcspn(previos, "\n")] = '\0';
    while(fgets(buffer, MAXSIZE, file) != NULL) {
      buffer[strcspn(buffer, "\n")] = '\0';
      if(!strcmp(buffer, previos)) {
        ++count;
      }
      else {
        if(count == 1)
          printf("%s\n", previos);
        strcpy(previos, buffer);
        count = 1;
      }
    }
    if(count == 1)
      printf("%s\n", previos);
    fclose(file);
  }

  if(flags == IGNORE) {
    FILE *file = fopen(argv[argc - 1], "r");
    char buffer[MAXSIZE], previos[MAXSIZE];
    fgets(previos, MAXSIZE, file);
    previos[strcspn(previos, "\n")] = '\0';
    while(fgets(buffer, MAXSIZE, file) != NULL) {
      buffer[strcspn(buffer, "\n")] = '\0';
      if(strcasecmp(buffer, previos)) {
        printf("%s\n", previos);
        strcpy(previos, buffer);
      }
    }
    printf("%s\n", previos);
    fclose(file);
  }

  if(flags == (UNIQUE | COUNT)) {
    FILE *file = fopen(argv[argc - 1], "r");
    int count = 1;
    char buffer[MAXSIZE], previos[MAXSIZE];
    fgets(previos, MAXSIZE, file);
    previos[strcspn(previos, "\n")] = '\0';
    while(fgets(buffer, MAXSIZE, file) != NULL) {
      buffer[strcspn(buffer, "\n")] = '\0';
      if(!strcmp(buffer, previos)) {
        ++count;
      }
      else {
        if(count == 1)
          printf("      %d %s\n", count, previos);
        strcpy(previos, buffer);
        count = 1;
      }
    }
    if(count == 1)
      printf("      %d %s\n", count, previos);
    fclose(file);
  }

  if(flags == (IGNORE | COUNT)) {
    FILE *file = fopen(argv[argc - 1], "r");
    int count = 1;
    char buffer[MAXSIZE], previos[MAXSIZE];
    fgets(previos, MAXSIZE, file);
    previos[strcspn(previos, "\n")] = '\0';
    while(fgets(buffer, MAXSIZE, file) != NULL) {
      buffer[strcspn(buffer, "\n")] = '\0';
      if(!strcasecmp(buffer, previos)) {
        ++count;
      }
      else {
        printf("      %d %s\n", count, previos);
        strcpy(previos, buffer);
        count = 1;
      }
    }
    printf("      %d %s\n", count, previos);
    fclose(file);
  }

  if(flags == (IGNORE | UNIQUE)) {
    FILE *file = fopen(argv[argc - 1], "r");
    int count = 1;
    char buffer[MAXSIZE], previos[MAXSIZE];
    fgets(previos, MAXSIZE, file);
    previos[strcspn(previos, "\n")] = '\0';
    while(fgets(buffer, MAXSIZE, file) != NULL) {
      buffer[strcspn(buffer, "\n")] = '\0';
      if(!strcasecmp(buffer, previos)) {
        ++count;
      }
      else {
        if(count == 1)
          printf("%s\n", previos);
        strcpy(previos, buffer);
        count = 1;
      }
    }
    if(count == 1)
      printf("%s\n", previos);
    fclose(file);
  }

  if(flags == (IGNORE | UNIQUE | COUNT)) {
    FILE *file = fopen(argv[argc - 1], "r");
    int count = 1;
    char buffer[MAXSIZE], previos[MAXSIZE];
    fgets(previos, MAXSIZE, file);
    previos[strcspn(previos, "\n")] = '\0';
    while(fgets(buffer, MAXSIZE, file) != NULL) {
      buffer[strcspn(buffer, "\n")] = '\0';
      if(!strcasecmp(buffer, previos)) {
        ++count;
      }
      else {
        if(count == 1)
          printf("      %d %s\n", count, previos);
        strcpy(previos, buffer);
        count = 1;
      }
    }
    if(count == 1)
      printf("      %d %s\n", count, previos);
    fclose(file);
  }
}
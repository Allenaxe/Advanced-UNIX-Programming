#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <getopt.h>
#include <stdlib.h>
#define MAXSIZE 20
#define COUNT 1
#define UNIQUE 2
#define IGNORE 4
#define UNKNOWN 0

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
      //default :
        //TODO
        //flags |= UNKNOWN;
        //break;
    }
  }
  

  //sorting
  FILE* file = fopen(argv[argc-1], "r");
  int file_length;
  char *buffer_line = 0;
  //get total line
  int line_count = 1;
  int ch;
  if (file == NULL){
    fclose(file);
    return 0;
  }
  while((ch = fgetc(file)) != EOF){
    if(ch == '\n')
      line_count++;
  }

  char **array = (char**)malloc(line_count *sizeof(char*));
  fseek(file, 0, SEEK_END);
  file_length = ftell(file);
  fseek(file, 0, SEEK_SET);
  buffer_line = malloc(file_length);
  if(buffer_line != NULL){
    fread(buffer_line, 1, file_length, file);
  }
  fseek(file, 0, SEEK_SET);
  if(buffer_line!= NULL){
    int x = 0, y = 0, z = 0;
    array[z] = malloc(MAXSIZE * sizeof(char));
    for(int i = 0; i < file_length; i++){
        
        if(buffer_line[i] != '\n'){
            // printf("%c", buffer_line[i]);
            array[z][y] = buffer_line[i];
            y++;
        }
        else if (buffer_line[i] == '\n'){
            // printf("%c\n", buffer_line[i]);
            y = 0;
            z++;
            array[z] = malloc(MAXSIZE * sizeof(char));
        }
    }
    char*temp = malloc(MAXSIZE*sizeof(char));
    for(int i = 0; i < line_count; i++){
        for(int j = i+1; j < line_count; j++){
            if (strcmp(array[i], array[j])>0){
                strcpy(temp, array[i]);
                strcpy(array[i], array[j]);
                strcpy(array[j], temp);
            }
        }
    }
  }
//   for(int i = 0; i < line_count; i++){
//     printf("%s\n", array[i]);
//   }
  fclose(file);
  FILE* wfile = fopen("temp.txt", "w+");
  if(!wfile){
    perror("open write file error\n");
  }
  for(int i = 0; i < line_count; i++){
    fputs(array[i], wfile);
    fputc('\n', wfile);
  }
  
  fclose(wfile);
    


  if(flags == COUNT) {
    FILE *file = fopen("temp.txt", "r");
    int count = 1, i = 0;
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
    FILE *file = fopen("temp.txt", "r");
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
    FILE *file = fopen("temp.txt", "r");
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
    FILE *file = fopen("temp.txt", "r");
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
    FILE *file = fopen("temp.txt", "r");
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
    FILE *file = fopen("temp.txt", "r");
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
    FILE *file = fopen("temp.txt", "r");
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

  if(flags == UNKNOWN){
    printf("Unknown arguments!\n");
  }
}

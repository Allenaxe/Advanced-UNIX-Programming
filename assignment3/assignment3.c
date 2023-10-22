#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>

#define READ 0x01
#define WRITE 0x02
#define APPEND 0x04

/*struct MEMORYSTREAM {
  char *buf;
  size_t realsize;
  size_t virtual_size;
  size_t currentpos;
  int flags;
};

int SETFLAG(const char *__restrict type) {
  int flags = 0;
  const char *pointer;
  for(pointer = type; *pointer; pointer++) {
    switch(*pointer) {
      case 'r':
        if(flags) return 0;
        flags |= READ;
        break;
      case 'w':
        if(flags) return 0;
        flags |= WRITE;
        break;
      case 'a':
        if(flags) return 0;
        flags |= APPEND;
        break;
      case '+':
        if(!flags) return 0;
        flags |= READ | WRITE;
        break;
      case 'b':
        if(!flags) return 0;

    }
  }
}

FILE *fmemopen(void *__restrict buf, size_t size, const char *__restrict type) {
  struct MEMORYSTREAM *memorystream;
  FILE *fp;

  if(size == 0) {
    errno = EINVAL;
    return NULL;
  }

  if((memorystream = malloc(sizeof(struct MEMORYSTREAM))) == NULL) {
    errno = ENOMEM;
    return NULL;

    if((memorystream->flags = SETFLAG(type)) == 0) {
      errno = EINVAL;
      return NULL;
    }
  }
}*/

#define MIN(a, b) ((a) < (b)) ? (a) : (b)
#define MAX(a, b) ((a) < (b)) ? (b) : (a)

struct MEMORYSTREAM {
  char *buf;
  size_t size;
  size_t rsize;
  size_t pos;
};

static int msread(void *cookie, char *buf, int len) {
  struct MEMORYSTREAM *memorystream = cookie;
  len = MIN(len, memorystream->size - memorystream->pos);
  memcpy(buf, memorystream->buf + memorystream->pos, len);
  memorystream->pos += len;
  return len;
}

static int mswrite(void *cookie, char *buf, int len) {
  struct MEMORYSTREAM *memorystream = cookie;
  len = MIN(len, memorystream->size - memorystream->pos);
  memcpy(memorystream->buf + memorystream->pos, buf, len);
  memorystream->pos += len;
  memorystream->rsize = MAX(memorystream->rsize, memorystream->pos);
  return len;
}

static fpos_t msseek(void *cookie, fpos_t offset, int whence) {
  struct MEMORYSTREAM *memorystream = cookie;
  switch (whence) {
    case SEEK_SET:
      memorystream->pos = offset;
      break;
    case SEEK_CUR:
      memorystream->pos += offset;
      break;
    case SEEK_END:
      memorystream->pos = memorystream->rsize + offset;
      break; 
  }
  return memorystream->pos;
} 

static int msclose(void *cookie) {
  free(cookie);
  return 0;
}

FILE *fmemopen(void *__restrict buf, size_t size, const char *__restrict type) {
  struct MEMORYSTREAM *memorystream = malloc(sizeof(struct MEMORYSTREAM));
  if(!memorystream) return NULL;
  memorystream->buf = buf;
  memorystream->size = size;
  memorystream->rsize = 0;
  memorystream->pos = 0;
  return funopen(memorystream, msread, mswrite, msseek, msclose);
}

int main()
{
  char buffer[100] = "";
  FILE* file = fmemopen(buffer, sizeof(buffer), "w+");
  if (file == NULL) {
    perror("fmemopen");
    return 1;
  }
  fwrite("hello world\0", 12, 1, file);
  char word[100] = "";
  char target[] = "world\0";
  fseek(file, 0, SEEK_SET);
  while(fread(word, 5, 1, file)) {
    if(!strcmp(word, target))
      break;
    fseek(file, 1, SEEK_CUR);
  }
  printf("%s\n", word);
  fseek(file, 0, SEEK_END);
  int len = ftell(file);
  fseek(file, 0, SEEK_SET);
  fread(word, len, 1, file);
  printf("%s\n", word);
  fclose(file);
}

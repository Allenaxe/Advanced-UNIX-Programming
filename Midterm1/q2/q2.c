#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/times.h>

#define BUFSIZE_1     1
#define BUFSIZE_32    32
#define BUFSIZE_1024  1024
#define BUFSIZE_4096  4096

static clock_t st_time;
static clock_t en_time;
static struct tms st_cpu;
static struct tms en_cpu;

void start_clock() { st_time = times(&st_cpu); }

void end_clock(char *msg)
{
    en_time = times(&en_cpu);
    fputs(msg, stdout);
    printf("Real Time: %lf, User Time %lf, System Time %lf\n",
        (double)(en_time - st_time) / 100,
        (double)(en_cpu.tms_utime - st_cpu.tms_utime) / 100,
        (double)(en_cpu.tms_stime - st_cpu.tms_stime) / 100);
}

void test_1()
{
  char buf_1[BUFSIZE_1];
  FILE *file = fopen("source2", "r");
  FILE *stream = fmemopen(buf_1, BUFSIZE_1, "r+");
  start_clock();
  while(fread(buf_1, BUFSIZE_1, 1, file)) {
    fwrite(buf_1, BUFSIZE_1, 1, stream);
  }
  end_clock("fread/fwrite with 1 bytes\n");
  FILE *output1 = fopen("output1", "w");
  fseek(file, 0, SEEK_SET);
  while(fread(buf_1, BUFSIZE_1, 1, file)) {
    fwrite(buf_1, BUFSIZE_1, 1, stream);
    fread(buf_1, BUFSIZE_1, 1, stream);
    fwrite(buf_1, BUFSIZE_1, 1, output1);
  }
  fclose(file);
  fclose(output1);
  fclose(stream);
}

void test_2()
{
  char buf_1[BUFSIZE_32];
  FILE *file = fopen("source2", "r");
  FILE *stream = fmemopen(buf_1, BUFSIZE_32, "r+");
  start_clock();
  while(fread(buf_1, BUFSIZE_32, 1, file)) {
    fwrite(buf_1, BUFSIZE_32, 1, stream);
  }
  end_clock("fread/fwrite with 32 bytes\n");
  FILE *output1 = fopen("output2", "w");
  fseek(file, 0, SEEK_SET);
  while(fread(buf_1, BUFSIZE_32, 1, file)) {
    fwrite(buf_1, BUFSIZE_32, 1, stream);
    fread(buf_1, BUFSIZE_32, 1, stream);
    fwrite(buf_1, BUFSIZE_32, 1, output1);
  }
  fclose(file);
  fclose(output1);
  fclose(stream);
}

void test_3()
{
  char buf_1[BUFSIZE_1024];
  FILE *file = fopen("source2", "r");
  FILE *stream = fmemopen(buf_1, BUFSIZE_1024, "r+");
  start_clock();
  while(fread(buf_1, BUFSIZE_1024, 1, file)) {
    fwrite(buf_1, BUFSIZE_1024, 1, stream);
  }
  end_clock("fread/fwrite with 1024 bytes\n");
  FILE *output1 = fopen("output3", "w");
  fseek(file, 0, SEEK_SET);
  while(fread(buf_1, BUFSIZE_1024, 1, file)) {
    fwrite(buf_1, BUFSIZE_1024, 1, stream);
    fread(buf_1, BUFSIZE_1024, 1, stream);
    fwrite(buf_1, BUFSIZE_1024, 1, output1);
  }
  fclose(file);
  fclose(output1);
  fclose(stream);
}

void test_4()
{
  char buf_1[BUFSIZE_4096];
  FILE *file = fopen("source2", "r");
  FILE *stream = fmemopen(buf_1, BUFSIZE_4096, "r+");
  start_clock();
  while(fread(buf_1, BUFSIZE_4096, 1, file)) {
    fwrite(buf_1, BUFSIZE_4096, 1, stream);
  }
  end_clock("fread/fwrite with 4096 bytes\n");
  FILE *output1 = fopen("output4", "w");
  fseek(file, 0, SEEK_SET);
  while(fread(buf_1, BUFSIZE_4096, 1, file)) {
    fwrite(buf_1, BUFSIZE_4096, 1, stream);
    fread(buf_1, BUFSIZE_4096, 1, stream);
    fwrite(buf_1, BUFSIZE_4096, 1, output1);
  }
  fclose(file);
  fclose(output1);
  fclose(stream);
}

void test_5()
{
  char buf_1[BUFSIZE_4096];
  FILE *file = fopen("source2", "r");
  FILE *stream = fmemopen(buf_1, BUFSIZE_4096, "r+");
  start_clock();
  while(fgets(buf_1, BUFSIZE_4096, file)) {
    fputs(buf_1, stream);
  }
  end_clock("fgets/fputs with 4096 bytes\n");
  FILE *output1 = fopen("output5", "w");
  fseek(file, 0, SEEK_SET);
  while(fgets(buf_1, BUFSIZE_4096, file)) {
    fputs(buf_1, stream);
    fgets(buf_1, BUFSIZE_4096, stream);
    fputs(buf_1, output1);
  }
  fclose(file);
  fclose(output1);
  fclose(stream);
}

void test_6()
{
  char buf_1[BUFSIZE_1];
  FILE *file = fopen("source2", "r");
  FILE *stream = fmemopen(buf_1, BUFSIZE_1, "r+");
  start_clock();
  int c;
  while((c = fgetc(file)) != EOF) {
    fputc(c, stream);
  }
  end_clock("fget/fput\n");
  FILE *output1 = fopen("output6", "w");
  fseek(file, 0, SEEK_SET);
  while((c = fgetc(file)) != EOF) {
    fputc(c, stream);
    fgetc(stream);
    fputc(c, output1);
  }
  fclose(file);
  fclose(output1);
  fclose(stream);
}

int main()
{
  test_1();
  test_2();
  test_3();
  test_4();
  test_5();
  test_6();
  return 0;
}
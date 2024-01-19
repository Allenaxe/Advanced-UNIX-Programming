#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <signal.h>
#include <unistd.h>

pthread_t T1, T2, T3;

void signal_handler(int signo) {
  switch (signo) {
    case SIGINT:
      printf("T1 handling SIGINT\n");
      break;
    case SIGTERM:
      printf("T2 handling SIGTERM\n");
      break;
    case SIGUSR1:
      printf("T3 handling SIGUSR1\n");
      break;
    }
}

void *T1_handler(void *arg) {
  sigset_t mask;
  sigemptyset(&mask);
  sigaddset(&mask, SIGTERM);
  sigaddset(&mask, SIGUSR1);
  pthread_sigmask(SIG_SETMASK, &mask, NULL);

  signal(SIGINT, signal_handler);
  while(1) sleep(1);
  return NULL;
}

void *T2_handler(void *arg) {
  sigset_t mask;
  sigemptyset(&mask);
  sigaddset(&mask, SIGINT);
  sigaddset(&mask, SIGUSR1);
  pthread_sigmask(SIG_SETMASK, &mask, NULL);

  signal(SIGTERM, signal_handler);

  while(1) sleep(1);
  return NULL;
}

void *T3_handler(void *arg) {
  sigset_t mask;
  sigemptyset(&mask);
  sigaddset(&mask, SIGINT);
  sigaddset(&mask, SIGTERM);
  pthread_sigmask(SIG_SETMASK, &mask, NULL);

  signal(SIGUSR1, signal_handler);
  while(1) sleep(1);
  return NULL;
}


int main() {

  pthread_create(&T1, NULL, T1_handler, NULL);
  pthread_create(&T2, NULL, T2_handler, NULL);
  pthread_create(&T3, NULL, T3_handler, NULL);

  sigset_t mask;
  sigemptyset(&mask);
  sigaddset(&mask, SIGINT);
  sigaddset(&mask, SIGTERM);
  sigaddset(&mask, SIGUSR1);
  pthread_sigmask(SIG_SETMASK, &mask, NULL);

  pthread_join(T1, NULL);
  pthread_join(T2, NULL);
  pthread_join(T3, NULL);

  while(1) sleep(1);

  return 0;
}

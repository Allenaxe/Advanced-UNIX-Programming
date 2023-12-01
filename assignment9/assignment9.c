#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

#define NUM_THREADS 5

struct barrier_t {
  int count;
  pthread_mutex_t mutex;
  pthread_cond_t cond;
};

struct barrier_t *barrier;

void barrier_init() {
  barrier = malloc(sizeof(struct barrier_t));
  barrier->count = 0;
  pthread_mutex_init(&barrier->mutex, NULL);
  pthread_cond_init(&barrier->cond, NULL);
}

void barrier_wait() {
  pthread_mutex_lock(&barrier->mutex);
  barrier->count++;

  if(barrier->count == 5) {
    barrier->count = 0;
    pthread_cond_broadcast(&barrier->cond);
  }
  else {
    pthread_cond_wait(&barrier->cond, &barrier->mutex);
  }

  pthread_mutex_unlock(&barrier->mutex);
}

void barrier_destroy() {
  barrier->count = 0;
  pthread_mutex_destroy(&barrier->mutex);
  pthread_cond_destroy(&barrier->cond);
}

void *thread_fn(void *arg) {
  printf("Starting thread %ld\n", (long)arg);

  barrier_wait();

  printf("Thread %u running\n", (unsigned int)pthread_self());
  return NULL;
}

int main() {
  
  pthread_t thread[NUM_THREADS];

  barrier_init();
  
  for(long i = 0; i < NUM_THREADS; ++i) {
    pthread_create(&thread[i], NULL, thread_fn, (void *)i);
    sleep(0.1);
  }

  for(long i = 0; i < NUM_THREADS; ++i)
    pthread_join(thread[i], NULL);
}
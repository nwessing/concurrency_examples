#include "errno.h"
#include "stdio.h"
#include "stdbool.h"
#include "stdlib.h"
#include "pthread.h"
#include "string.h"

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

long get_num_theads(int argc, char **argv);
bool get_use_mutex_option(int argc, char **argv);
void *increment(void *data);
void *increment_with_mutex(void *data);

int main(int argc, char **argv) {
  long num_threads = get_num_theads(argc, argv);
  bool use_mutex = get_use_mutex_option(argc, argv);
  if (num_threads < 0) {
    return 1;
  }

  if (use_mutex) {
    printf("Using a mutex\n");
  }

  int result = 0;

  pthread_t *threads = calloc(sizeof(pthread_t), num_threads);
  for (int i = 0; i < num_threads; ++i) {
    if (use_mutex) {
      pthread_create(&threads[i], NULL, increment_with_mutex, &result);
    } else {
      pthread_create(&threads[i], NULL, increment, &result);
    }
  }

  for (int i = 0; i < num_threads; ++i) {
    pthread_join(threads[i], NULL);
  }

  free(threads);

  printf("Result is %i\n", result);
}

void *increment(void *data) {
  int *value = (int*) data;
  *value += 1;
  return NULL;
}

void *increment_with_mutex(void *data) {
  int *value = (int*) data;

  pthread_mutex_lock(&mutex);
  *value += 1;
  pthread_mutex_unlock(&mutex);

  return NULL;
}

long get_num_theads(int argc, char **argv) {
  long num_threads;
  if (argc < 2) {
    printf("Must call this program with 1 argument, indicating the number of threads");
    return -1;
  } else {
    errno = 0;
    num_threads = strtol(argv[1], NULL, 10);
    if (errno) {
      printf("Please provide a valid integer\n");
      return -1;
    }
  }

  return num_threads;
}

bool get_use_mutex_option(int argc, char **argv) {
  if (argc < 3) {
    return false;
  }

  char *arg = argv[2];
  if (strcmp("-m", arg) == 0) {
    return true;
  }

  if (strcmp("-M", arg) == 0) {
    return true;
  }

  return false;
}


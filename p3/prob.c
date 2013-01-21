#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <pthread.h>

int nr;
pthread_mutex_t mutex;

void* thread_func(void* arg) {
    char* cuvant = (char*)malloc(40);
    cuvant = (char*)arg;

    int i;
    for (i = 0; i < strlen(cuvant); i++) {
      if (cuvant[i] == 'a' || cuvant[i] == 'e' || cuvant[i] == 'i' ||
          cuvant[i] == 'o' || cuvant[i] == 'u') {
        pthread_mutex_lock(&mutex);
        nr++;
        pthread_mutex_unlock(&mutex);
      }
    }
    return 0;
}

int main(int argc, char* argv[]) {
  if (argc == 1) {
    printf("Trebuie sa dat parametrii \n");
  }

  pthread_t threads[20];

  pthread_mutex_init(&mutex,NULL);
  int i;
  for (i = 1; i < argc; i++) {
    if (pthread_create(&threads[i],NULL,thread_func,argv[i]) < 0) {
      printf("Eroare la thread \n");
    }
  }

  for (i = 1; i < argc;i++) {
    pthread_join(threads[i],NULL);
  }

  printf("Au fost %d vocale in argumentele date \n",nr);

  pthread_mutex_destroy(&mutex);
  return 0;
}

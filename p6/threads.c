#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <pthread.h>
#include <time.h>

char sir[100];
pthread_mutex_t mutex[100];

void* thread_func(void* arg) {
   int t =  time(NULL);
   while (time(NULL) - t < 15) {
      int index = rand()%100;
      const char alphanum[80] = "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNNOPQRSTUVWXYZ";
      char c = alphanum[rand() % (strlen(alphanum) -1) ];
      sleep(rand()%3);
      pthread_mutex_lock(&mutex[index]);
      sir[index] = c;
      printf("%s \n",sir);
      pthread_mutex_unlock(&mutex[index]);
   }
}

int main() {
  int i;
  for (i = 0; i<100; i++) {
    pthread_mutex_init(&mutex[i],NULL);
  }

  sir[100] = '\0';
  pthread_t threads[50];
  for (i = 0; i < 50; i++) {
    pthread_create(&threads[i],NULL,thread_func,NULL);
  }

  for (i = 0; i < 50; i++) {
    pthread_join(threads[i],NULL);
  }
  printf("Sirul rezultant este %s \n",sir);
  for (i = 0; i<100; i++) {
    pthread_mutex_destroy(&mutex[i]);
  }
  return 0;
}

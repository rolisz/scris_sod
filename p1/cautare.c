#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void* thread_start(void* arg) {
  char* file = (char*)malloc(strlen((char*)arg));
  strcpy(file,arg);
  printf("%s \n",file);
  FILE* f = fopen(file,"r");

  if (f == NULL) {
    printf("File %s not found \n",file);
    return 0;
  }
  char s[100];
  int i = 0;
  while (fgets(s,100,f)) {
    if (strstr(s,"Cautare") != NULL) {
      i++;
    }
  }
  fclose(f);
  printf("In fisierul %s Cautare a fost gasit de %d ori \n",file, i);
  return 0;
}

int main(int argc, char* argv[]) {
  if (argc == 1) {
    printf("Dati fisiere \n");
    exit(1);
  }
  pthread_t* threads = (pthread_t*)malloc(sizeof(pthread_t)*(argc));

  int i;
  for (i = 1; i < argc; i++) {
//    printf("%s \n",argv[i]);
    int s = pthread_create(&threads[i],NULL,&thread_start,argv[i]);
    if (s < 0) {
      printf("Eroare la thread \n");
    }
  }

  for (i = 1; i < argc; i++) {
    pthread_join(threads[i],NULL);
  }
  return 0;
}

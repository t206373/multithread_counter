/* Data de submissao:16/07/2020
 * Nome: Tony Tian Rui Li
 * RA:206373
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>

#define MAX 4

pthread_mutex_t key;
int num[99999], prime[99999];
int n;
/*VERIFICADOR DE NUMEROS PRIMOS, RETORNA 0 PARA NAO-PRIMO E 1 PARA PRIMO.*/
int primetest (int entry) {
  if (entry < 2)
    return 0;
  for (int i = 2; i < entry; i++)
    if (entry % i == 0)
      return 0;
  return 1;
}

void* thread() {
  int inst=0;
  while (1) {/*THREADPOOL*/
    pthread_mutex_lock(&key);
    while ((num[inst] == 0) && (inst < n)) {/*VERIFICA SE O NUMERO JA FOI ANALISADO.*/
      inst++;
    }
    if (inst == n) {/*SE NAO TIVER MAIS NUMERO PARA ANALISAR, ENCERRA O THREAD.*/
      pthread_mutex_unlock(&key);
      break;
    }
    prime[inst] = primetest(num[inst]);
    num[inst] = 0;
    pthread_mutex_unlock(&key);
  }
  return NULL;
}

int main() {
  pthread_t threads[MAX];
  int thread_id[MAX];
  int entry, x;
  /*LENDO E ESCREVENDO AS ENTRADAS NO VETOR NUM.*/
  do {
    scanf("%d", &entry);
    num[n] = entry;
    prime[n] = 0;
    n++;
  }
  while((entry=getchar()) != '\n');
  /*CRIANDO E IDENTIFICANDO THREADS.*/
  for (int i = 0; i < MAX; i++) {
    thread_id[i] = i;
  }

  for (int i = 0; i < MAX; i++) {
    pthread_create(&(threads[i]), NULL, thread, (void*) (&thread_id[i]));
  }
  /*ESPERANDO ENCERRAR TODOS OS THREADS.*/
  for (int i = 0; i < MAX; i++) {
    pthread_join(threads[i], NULL);
  }
  /*CALCULANDO E IMPRIMINDO QUANTIDADE DE NUMEROS PRIMOS EXISTENTES NA ENTRADA.*/
  for (int i = 0; i < n; i++) {
    x += prime[i];
  }
  printf("%d\n", x);
  return 0;
}
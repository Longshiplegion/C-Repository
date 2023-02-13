#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <fcntl.h>
#define max_deposits 1000000

int balance = 0;
int depositAmount = 1;
sem_t* mutex;


void *deposit(void *a)
{
  int x,tmp;

  for(x=0;x<max_deposits;x++)
  {
    sem_wait(mutex);

    tmp = balance;
    tmp = tmp + depositAmount;
    balance = tmp;

    sem_post(mutex);
  }
  return NULL;
}

int main(void)
{
  pthread_t tid1, tid2;

  mutex = sem_open("mutex", O_CREAT, 00644, 1);

  if(mutex == SEM_FAILED)
  {
   printf("\n error creating mutex");
   exit(1);
  }

  if(pthread_create(&tid1,NULL,deposit,NULL))
  {
    printf("\n Error creating thread1");
    exit(1);
  }
  if(pthread_create(&tid2,NULL,deposit,NULL))
  {
    printf("\n Error creating thread2");
    exit(1);
  }

  if(pthread_join(tid1,NULL))
  {
    printf("Error Joining thread 1");
    exit(1);
  }

  if(pthread_join(tid2,NULL))
  {
    printf("Error Joining thread 1");
    exit(1);
  }

  if (balance < 2 * max_deposits)
  {
    printf("Bad Balance is $%d and should be $%d\n",balance,2 * max_deposits);
  }
  else
  {
    printf("Good Balance is $%d\n",balance);
  }
  sem_close(mutex);
  pthread_exit(NULL);
}

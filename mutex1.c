#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define max_deposits 1000000

int balance = 0;

void *deposit(void *a)
{
  int x,tmp;

  for(x=0;x<max_deposits;x++)
  {
    tmp = balance;
    tmp = tmp + 1;
    balance = tmp;
  }
  return NULL;
}

int main()
{
  pthread_t tid1, tid2;

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
    printf("Bad Balance is $%d and should be $%d\n");
  }
  else
  {
    printf("Good Balance is $%d",balance);
  }
  pthread_exit(NULL);
}

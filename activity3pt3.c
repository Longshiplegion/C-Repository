#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <signal.h>
#include <semaphore.h>
#include <pthread.h>
#include <sys/mman.h>

sem_t* semaphore;
pid_t otherPid;
sigset_t sigSet;

void signalHandler1(int signum)
{
  printf("Caught Signal %d\n",signum);
  printf("Exit Child Process\n");
  sem_post(semaphore);
  _exit(0);
}

void signalHandler2(int signum)
{
  printf("I am alive\n");
}

void childProcess()
{
  signal(SIGUSR1,signalHandler1);
  signal(SIGUSR2,signalHandler2);

  int value;
  sem_getvalue(semaphore,&value);
  printf("Child Process semaphore count is %d\n",value);
  printf("Child Process is grabbing semaphore\n");
  sem_wait(semaphore);
  sem_getvalue(semaphore,&value);
  printf("Child Process Semaphore Count is %d\n",value );
  printf("Starting very long child Process");
  for(int x=0; x < 60;++x)
  {
    printf(".\n");
    sleep(1);
  }
  sem_post(semaphore);

  printf("Exit Child Process\n");
  _exit(0);

}
void *checkHungChild(void *a)
{
  int* status = a;
  sleep(10);
  if(sem_trywait(semaphore) != 0)
  {
      printf("Child Process appears to be hung..\n");
      *status = 1;
  }
  else
  {
      printf("Child Process Seems to be running fine\n");
      *status = 0;
  }
  return NULL;
}

void parentProcess()
{
  sleep(2);

  if(getpgid(otherPid) >= 0)
  {
    printf("Child Process is running\n");
  }

  int value;
  sem_getvalue(semaphore,&value);
  printf("In the Parent process with the count of %d\n",value);

  if(sem_trywait(semaphore) != 0)
  {
    pthread_t tid1;
    int status = 0;
    printf("Detected Child is hung or running to long\n");
    if(pthread_create(&tid1,NULL,checkHungChild,&status))
    {
      printf("ERROR creating timer thread \n");
      _exit(1);
    }
    if(pthread_join(tid1,NULL))
    {
      printf("Error joining timer thread\n");
      exit(1);
    }
    if(status == 1)
    {
      printf("Going to kill the child proccess with id of %d\n",otherPid);
      kill(otherPid,SIGTERM);
      printf("Child Process taken out\n");

      printf("Sending Proof\n");
      sleep(5);
      kill(otherPid,SIGUSR2);
      sleep(1);
      printf("Proof submitted\n");

      sem_getvalue(semaphore,&value);
      printf("In the Parent process with semaphor count of %d\n",value);
      if(sem_trywait(semaphore) != 0)
      {
          if(value ==0)
            sem_post(semaphore);
          printf("Cleaned up and caught the semaphore\n");
          sem_getvalue(semaphore,&value);
          printf("in the parent process with the count of %d\n",value );

      }
      else
      {
        printf("Finally caught the runner\n");
      }
    }
  }
  printf("Exiting the parent process\n");
  _exit(0);
}

int main(int argc, char const *argv[]) {
  pid_t pid;
  semaphore = (sem_t*)mmap(0,sizeof(sem_t),PROT_READ|PROT_WRITE,MAP_SHARED|MAP_ANONYMOUS,-1,0);
  if(sem_init(semaphore,1,1) != 0)
  {
    printf("failed to create semaphore\n");
    exit(EXIT_FAILURE);
  }

  pid = fork();

  if(pid == -1)
  {
    printf("Cant fork\n");
    exit(EXIT_FAILURE);
  }
  if(pid == 0)
  {
    printf("Started child process with ID of %d\n",getpid());
    otherPid = getpid();
    childProcess();
  }
  else
  {
    printf("Starting Parent Process with ID of %d\n",getpid());
    otherPid = pid;
    parentProcess();
  }
  sem_destroy(semaphore);
  return 0;
}

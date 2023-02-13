#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/mman.h>
#include <error.h>
#include <errno.h>

int WAKEUP = SIGUSR1;

pid_t otherPid;
sigset_t sigSet;

void sleepTillWoken()
{
  int nSig;

  printf("Sleeping....\n");
  sigwait(&sigSet,&nSig);
  printf("Awoken\n");
}

void consumer()
{
  sigemptyset(&sigSet);
  sigaddset(&sigSet,WAKEUP);
  sigprocmask(SIG_BLOCK,&sigSet,NULL);

  printf("putting the consumer to sleep forever\n");
  sleepTillWoken();

  int count = 0;
  printf("Running Consumer Process\n");

  while(count < 20)
  {
    printf("consumer %d\n",count);
    sleep(1);
    ++count;

  }
  _exit(1);

}

void producer()
{
  int count = 0;
  printf("Running producer process\n");

  while(count < 30)
  {
    printf("Producer %d\n",count);
    sleep(1);
    if(count == 5)
    {
      printf("Waking Consumer\n");
      kill(otherPid,WAKEUP);
    }
    ++count;
  }
  _exit(1);
}

int main(int argc, char* argv[]) {

  pid_t pid;

  pid = fork();
  if(pid == -1)
  {
    printf("Cant fork error %d\n");
  }
  if(pid == 0)
  {
    otherPid = getppid();
    producer();
  }
  else
  {
    otherPid = pid;
    consumer();
  }
  /* code */
  return 0;
}

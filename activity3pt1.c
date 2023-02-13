#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <sys/mman.h>
#include <errno.h>

int MAX = 100;
int WAKEUP = SIGUSR1;
int SLEEP = SIGUSR2;

pid_t otherPid;
sigset_t sigSet;

struct CIRCULAR_BUFFER
{
  int count;
  int lower;
  int upper;
  int buffer[100];
};

struct CIRCULAR_BUFFER *buffer = NULL;

void sleepAndWait()
{
  int nSig;

  printf("Sleeping\n");
  sigwait(&sigSet, &nSig);
  printf("Awoken\n");
}

void wakeupOther()
{
    kill(otherPid,WAKEUP);
}

int getValue()
{
  int value = buffer->buffer[buffer->lower];
  printf("Consumer Read value of %c\n",value);
  ++buffer->lower;
  if(buffer->lower == MAX)
  {
    buffer->lower = 0;
  }
  --buffer->count;
  return value;


}

void putValue(int value)
{
  buffer->buffer[buffer->upper] = value;
  printf("Produce store value  of %c\n",buffer->buffer[buffer->upper]);
  ++buffer->upper;
  if(buffer->upper == MAX)
  {
    buffer->upper = 0;

  }
  ++buffer->count;

}

void consumer()
{
  sigemptyset(&sigSet);
  sigaddset(&sigSet, WAKEUP);
  sigprocmask(SIG_BLOCK,&sigSet,NULL);

  printf("Running the Child Consumer Process \n");
  int character = 0;
  do
  {
      sleepAndWait();
      character = getValue();
  }while(character != 0);

  printf("Exiting the Child Consumer Process\n");
  _exit(1);
}

void producer()
{
  int value = 0;

  printf("Running the Parent Producer Process");

  char message[10] = "Andrew";
  for(int x = 0;x<strlen(message);++x)
  {
    putValue(message[x]);
    wakeupOther();
    sleep(1);
  }

  putValue(0);
  wakeupOther();
  printf("Exiting the Parent Producer Process\n");
  _exit(1);
}

int main(int argc, char* argv[]) {
  pid_t pid;
  buffer = (struct CIRCULAR_BUFFER*)mmap(0,sizeof(buffer),PROT_READ|PROT_WRITE,MAP_SHARED|MAP_ANONYMOUS,-1,0);
  buffer->count = 0;
  buffer->lower = 0;
  buffer->upper = 0;

  pid = fork();
  if (pid == -1)
  {
    printf("Cant fork error\n");
    exit(EXIT_FAILURE);
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
  return 0;
}

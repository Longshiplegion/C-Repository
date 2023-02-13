#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <error.h>
#include <errno.h>

pthread_mutex_t mutex;
long counter;
time_t end_time;

void *counter_thread (void *arg)
{
  int status;

  while(time (NULL) < end_time)
  {
    status = pthread_mutex_lock (&mutex);
    if (status == 0)
        printf("Counter Thread: Locked Mutex for Counter for incrementation\n");
    ++counter;
    status = pthread_mutex_unlock (&mutex);
    if (status == 0)
        printf("Counter Thread: Unlocked muted for counter since we are done\n");

    sleep(1);
  }
  printf("Final Counter is %lu\n",counter);
  return NULL;
}

void *monitor_thread (void *arg)
{
  int status;
  int misses = 0;

  while(time (NULL) < end_time)
  {
    sleep(3);

    status = pthread_mutex_trylock (&mutex);
    if(status != EBUSY)
    {
      printf("Monitor Thread: the trylock will lock the mutex so we can safely read the counter\n");
      printf("Monitor Thread: The Counter from Monitor is %ld\n",counter);
      status =pthread_mutex_unlock (&mutex);
      if (status == 0)
      {
        printf("Monitor Thread: will now unlock the mutex since we are done\n");
      }
      else
      {
        ++misses;
      }
    }
  }
  printf("Final monitor thread was missed %d times.\n",misses );
  return NULL;
}

int main(int argc, char* argv[]) {
  int status;
  pthread_t counter_thread_id;
  pthread_t monitor_thread_id;

  pthread_mutex_init(&mutex,0);
  end_time = time (NULL) + 60;

  if(pthread_create(&counter_thread_id,NULL,counter_thread,NULL))
  {
    printf("Failed creating counter thread\n");
  }
  if(pthread_create(&monitor_thread_id,NULL,monitor_thread,NULL))
  {
    printf("Failed to create monitor thread\n");
  }

  if(pthread_join(counter_thread_id,NULL))
  {
    printf("Joined counter thread failed\n");
  }
  if(pthread_join(monitor_thread_id,NULL))
  {
    printf("Joined Monitor Thread Failed\n");
  }
  return 0;
}

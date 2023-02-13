#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <spawn.h>
#include <string.h>
extern char **environ;


void run_cmd(char *cmd)
{
  pid_t pid;
  char *argv[] = {"sh","-c",cmd,NULL};
  int status;

  printf("Running Command.......%s\n",cmd);
  status = posix_spawn(&pid,"/bin/sh",NULL,NULL,argv,environ);
  if(status==0)
  {
    printf("Child process ID (PID) is %i\n");
    if(waitpid(pid,&status,0) != -1)
    {
      printf("child process exited with status of %i\n",status);
    }
    else
    {
      perror("failed to wait for child process");
    }
  }
  else
  {
    printf("Child process has failed to spaw with error of '%s'\n");
  }
}
int main(int argc,char* argv[])
{
  run_cmd(argv[1]);
  return 0;
}

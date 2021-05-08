#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<unistd.h>
#include<wait.h>
#include<fcntl.h>

void    loop_pipe(char ***cmd);

int main()
{
  char *ps[] = {"ps", "aux", NULL};
  char *sort[] = {"sort", "-nrk", "3,3", NULL};
  char *head[] = {"head", "-5", NULL};
  char **cmd[] = {ps, sort, head, NULL};

  loop_pipe(cmd);
  return (0);
}

void    loop_pipe(char ***cmd) 
{
  int   p[2];
  pid_t pid;
  int   fd_in = 0;

  while (*cmd != NULL)
    {
      pipe(p);
      if ((pid = fork()) == -1)
        {
          exit(EXIT_FAILURE);
        }
      else if (pid == 0)
        {
          dup2(fd_in, 0); //change the input according to the old one 
          if (*(cmd + 1) != NULL)
            dup2(p[1], 1);
          close(p[0]); //menutup input pipe
          execvp((*cmd)[0], *cmd);
          exit(EXIT_FAILURE);
        }
      else
        {
          wait(NULL);
          close(p[1]); //menutup output pipe
          fd_in = p[0]; //menyimpan input untuk loop selanjutnya
          cmd++;
        }
    }
}

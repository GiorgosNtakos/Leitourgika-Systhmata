#include <stdio.h>
#include <stdlib.h>

int main()
{
 int pid1;
 int pid2;
 pid1 = fork();

 if (pid1 < 0)
  printf("Could not create any child\n");
 else
 {
  pid2 = fork();
 if (pid2 < 0)
  printf("Could not create any child\n");
 else if ( (pid1 < 0) && (pid2 < 0))
  kill(pid1,9);
 }
printf("I am process %d, my father is %d. Im going to sleep.\n",getpid(),getppid());
sleep(20);
return (0);
}

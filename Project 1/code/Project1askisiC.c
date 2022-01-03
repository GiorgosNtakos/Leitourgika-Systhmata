#include<stdio.h>
#include<stdlib.h>

int main()
{

 int i=0,pid;
 
 for(i=0;i<10;i++)
 {
   pid=fork();
   if(pid==0)
   {
     printf("[son] pid %d from [parent] pid %d\n",getpid(),getppid());
   }
   else goto end; //O pateras paei sto wait(NULL) kai perimenei na teleiwsoun
				  //ta paidia kai den genaei pleon allo.
 }
 end:
 wait(NULL);
 return(0);
}

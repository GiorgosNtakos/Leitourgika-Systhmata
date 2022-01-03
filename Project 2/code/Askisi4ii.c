#include<stdio.h>
#include<stdlib.h>
#include<semaphore.h> 
#include <fcntl.h> 

typedef sem_t Semaphore;


Semaphore *synch1;
Semaphore *synch2;
Semaphore *synch3;
Semaphore *synch4;

int main()
{
 int i,x=0;
 pid_t pid[4];

 synch1 = sem_open ("Sem1", O_CREAT | O_EXCL, 0644, 0);        
 synch2 = sem_open ("Sem2", O_CREAT | O_EXCL, 0644, 0);
 synch3 = sem_open ("Sem3", O_CREAT | O_EXCL, 0644, 0);
 synch4 = sem_open ("Sem4", O_CREAT | O_EXCL, 0644, 0);


 for(i=0;i<=5;i++)
 {
  pid[i]=fork();
  if(pid[i]<0)
   {printf("Fork Error!\n");}
  else if(pid[i]==0)
   {break;}
 }


 if(pid[0]==0)            //P1
 { 
  system("ls -l");
  printf("1\n");
  sem_post(synch1);
  sem_post(synch1);
 }


 if(pid[1]==0)            //P2
 {
  sem_wait(synch1);
  system("ps -l");
  printf("2\n");
  sem_post(synch2);
  sem_post(synch2);
 }


 if(pid[2]==0)            //P3
 {
  sem_wait(synch1);
  system("ls -l");
  printf("3\n");
  sem_post(synch3);
  sem_post(synch3);
 }

 

 if(pid[3]==0)            //P4
 {
  sem_wait(synch2);
  system("ps -l");
  printf("4\n");
  sem_post(synch4);
 }


 
 if(pid[4]==0)             //P5
 {
  sem_wait(synch2);
  sem_wait(synch3);
  system("ps -l");
  printf("5\n");
 }



 if(pid[5]==0)                 //P6
 {
  sem_wait(synch3);
  sem_wait(synch4);
  system("ls -l");
  printf("6\n");
 }



sem_unlink ("Sem1");
sem_close(synch1);
sem_unlink ("Sem2");
sem_close(synch2); 
sem_unlink ("Sem3");
sem_close(synch3);
sem_unlink ("Sem4");
sem_close(synch4); 


return(0);

}

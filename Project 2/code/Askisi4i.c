#include<stdio.h>
#include<stdlib.h>
#include<semaphore.h> 
#include <fcntl.h> 

typedef sem_t Semaphore;

Semaphore *synch13;
Semaphore *synch23;
Semaphore *synch34;
Semaphore *synch35;


int main()
{
 int i;
 pid_t pid[4];
 
 synch13 = sem_open ("Sem1", O_CREAT | O_EXCL, 0644, 0);
 synch23 = sem_open ("Sem2", O_CREAT | O_EXCL, 0644, 0);
 synch34 = sem_open ("Sem3", O_CREAT | O_EXCL, 0644, 0);
 synch35 = sem_open ("Sem4", O_CREAT | O_EXCL, 0644, 0);

 for(i=0;i<5;i++)
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
  printf("\n");
  sem_post(synch13);
 }


 if(pid[1]==0)           //P2
 {
  system("ps -l");
  printf("\n");
  sem_post(synch23);
 }

 if(pid[2]==0)            //P3
 {
  sem_wait(synch13);
  sem_wait(synch23);
  
  system("ls -l");
  printf("\n");
  
  sem_post(synch34);
  sem_post(synch35);
 }
 
 if(pid[3]==0)           //P4
 {
  sem_wait(synch34);
  system("ps -l");
  printf("\n");
 }

 if(pid[4]==0)           //P5
 {
  sem_wait(synch35);
  system("ls -l");
  printf("\n");
 }


sem_unlink ("Sem1");   
sem_close(synch13);  
sem_unlink ("Sem2");   
sem_close(synch23); 
sem_unlink ("Sem3");   
sem_close(synch34);  
sem_unlink ("Sem4");   
sem_close(synch35); 

return(0);
}

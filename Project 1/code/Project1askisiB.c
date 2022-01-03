#include<stdio.h>
#include<stdlib.h>

int main()
{

 int i=0;

 for(i=0;i<10;i++)
 {
   if(fork()==0)     //Dimiourgei paidi kai ektelei to printf MONO to paidi.
   {
     printf("[son] pid %d from [parent] pid %d\n",getpid(),getppid());
     exit(0);        //Termatizei to paidi gia na mhn treksei pera apo auto to simeio.
   }
 }
 return(0);
}

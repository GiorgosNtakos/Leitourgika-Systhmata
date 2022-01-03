#include <stdio.h>         
#include <stdlib.h>                      
#include <semaphore.h>      
#include <fcntl.h> 
#include <sys/mman.h>


#define max 100
#define PAGESIZE 4096

sem_t *synch;
int *heap;
int *size;


void heapifyUp(){    //Yporoytina poy ektelei thn diadikasia Heapify Up
    int i = *size;

    while(1){
        int parent = i/2;
        if (parent > 0 && heap[parent] > heap[i]){
            int t = heap[parent];
            heap[parent] = heap[i];
            heap[i]=t;
            i = parent;
        } else {
            break;
        }
    }
}

void insert(int key){  //Yporoytina poy ektelei thn diadikasia insert 
    *size = *size + 1;
    heap[*size] = key;
    heapifyUp();
}

void printHeap(){   //Yporoytina poy typwnei to dentro
    int i = 1;
    while(i <= *size){
        printf("%d ",heap[i]);
        i++;
    }
    printf("\n");
}

int main()
{
 int i=0,pid,value;
 synch = sem_open ("Sem1", O_CREAT | O_EXCL, 0644, 1);

 size = mmap(0,sizeof(int), PROT_READ|PROT_WRITE,                 //Dhmiourgeia koinhs mnhmhs gia thn metavlhth size
              MAP_SHARED | MAP_ANONYMOUS, -1, 0);
 
 heap = mmap(0, max*sizeof(int), PROT_READ|PROT_WRITE,            //Dhmiourgeia koinhs mnhmhs gia ton pinaka heap
              MAP_SHARED | MAP_ANONYMOUS, -1, 0);

 for(i=0;i<100;i++)                                          //Dhmiourgeia ypodiergasiwn
 {
  pid=fork();
  if(pid<0)
   {printf("Fork Error!\n");}
  else if(pid==0)
   {break;}
 }

 sem_wait(synch);                                           //Arxh Krisimhs Perioxhs

 int upper=1000,lower=0;                                    // Tropopoihsh wste na perioristoun oi tyxaioi arithmoi
 srand(time(NULL) ^ (getpid()<<16));                        // se evros timwn metaksy tou 0 kai toy 1000.
 value=(rand() % (upper - lower + 1)) + lower;              
  

 insert(value);

 sem_post(synch);                                           //Telos Krisimhs Perioxhs

 sem_unlink ("Sem1");   
 sem_close(synch);  
 
 if(pid>0)
 {printHeap();}                                             //Ektypwsh apo ton patera

return(0);
}


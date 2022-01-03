#include<stdio.h>
#include<stdlib.h>

void foo();

int main()
{
	time_t start,end;
	int i=1,pid=1;
	long double temp;
	start=time(NULL);
	printf("Initial value of seconds: %ld \n",start);
	
	while (i<=10000 && pid>0) 	//Exoume valei 10000 giati me mikrotera i 
	{							//to programma teleiwne se ligotero apo 1 
		i=i+1;					//deuterolepto, enw gia megalytera den 
		pid=fork();				//evgaze kan apotelesmata.
		if (pid==0) foo();		
		
	}
	
	i=1;
	while (i<=10000 && pid>0)
	{
		i=i+1;
		waitpid();
	}
	if (pid>0)
	{
		end=time(NULL);
		printf("Finishing value of seconds: %ld \n",end);
	
		temp=end-start;
		printf("Completion time=%Lf seconds.\n",temp);
		temp=temp/10000;
		printf("Average execution time: %Lf seconds per proccess.\n",temp);
	}	
	return (0);
}
		
	
	

void foo()
{
	int x=0;
	x=x+10;
}
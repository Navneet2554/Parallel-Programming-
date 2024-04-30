#include<omp.h>// this is OpenMP header file
#include<stdio.h>
#include<stdlib.h>
int main()
{
	#pragma omp parallel
	{
	printf("Hello world thread no. %d from, core no.%d\n" ,omp_get_thread_num() , sched_getcpu());
	}
return 0;
}

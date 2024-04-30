#include<stdio.h>
#include<stdlib.h>
#include<omp.h>


#define MAX_SIZE 10000
#define MAX_THREAD 4

int main(){
	int arr[MAX_SIZE],i,tid,numt,psum;
	int sum=0;
	for(int i=0;i<MAX_SIZE;i++){
		arr[i]=1;
	}

	#pragma omp parallel default (shared) private (i,tid,psum)
	{
		int from,to, psum=0;
		tid=omp_get_thread_num();
		numt=omp_get_num_threads();

		from=(MAX_SIZE/numt)*tid;
		to=(MAX_SIZE/numt)*(tid+1)-1;

		if(tid==numt-1)
			to=MAX_SIZE-1;

		for(i=from;i<=to;i++){
			psum+=arr[i];
		}

		printf("Executing thread %d with sum : (%d)\n",tid,psum);


		#pragma omp parallel
		{
			sum+=psum;
		}
	}
	printf("Sum of array element is : %d\n",sum);

	return 0;
}

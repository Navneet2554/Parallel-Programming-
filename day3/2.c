#include<stdio.h>
#include<omp.h>
#define asize 10000
int main()
{
	int a[asize],i,tid,numt,psum,sum=0;
	//double t1,t2;
	for(i=0;i<10000;i++)
		a[i]=1;
	#pragma omp paralel default (shared) private (i,tid,psum)
	{
		int from,to,psum=0;
		tid=omp_get_thread_num();
		numt=omp_get_num_threads();
		from=(asize/numt)*tid;
		to=(asize/numt)*(tid+1)-1;
		if(tid==numt-1)
			to=asize-1;
		for(i=0;i<asize;i++)
			psum=psum+a[i];
		#pragma omp critical
		{
			sum=sum+psum;
		}
	}
	printf("first sum:%d",sum);
}

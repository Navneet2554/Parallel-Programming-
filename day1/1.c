#include<stdio.h>
#include<omp.h>
int main(){
	double start,end;
	start = omp_get_wtime();
	for(int i=1;i<=100;i++)
		printf(" smit ");
	end = omp_get_wtime();
printf("Execution Time = %f",end-start);
return 0;
}

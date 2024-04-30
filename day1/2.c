#include<stdio.h>
#include<stdlib.h>
int main()
{
	for( int i=1;i<10000;i++)
	printf("%d\n", rand()%1000+0);

	return 0;
}

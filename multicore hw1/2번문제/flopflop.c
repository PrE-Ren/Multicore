#include<stdio.h>
#include<time.h>
#include <math.h>
#include <stdlib.h>

void main(void)
{
	float a = 6.0f;
	float b = 3.0f;
	float c = 0.0f;
	double d = 6;
	double e = 3;
	double f = 0;

	struct timespec start,end;

	clock_gettime(CLOCK_REALTIME, &start);	
	for (int i=0;i<100000000;i++)
	{
	    c = a*b+a-b;
	}
	clock_gettime(CLOCK_REALTIME, &end);
	printf("32bit elapsed time (sec) : %.9lf\n", (end.tv_sec - start.tv_sec) + (double)(end.tv_nsec - start.tv_nsec)/1000000000);
	
	clock_gettime(CLOCK_REALTIME, &start);	
	for(int i=0;i<100000000;i++)
	{
	    f = d*e+d-e;
	}
	clock_gettime(CLOCK_REALTIME, &end);
	printf("64bit elapsed time (sec) : %.9lf\n", (end.tv_sec - start.tv_sec) + (double)(end.tv_nsec - start.tv_nsec)/1000000000);
	printf("%f, %lf\n",c,f);
}

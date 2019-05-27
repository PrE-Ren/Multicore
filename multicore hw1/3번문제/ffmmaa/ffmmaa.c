#include<stdio.h>
#include<time.h>
#include<math.h>
#include<stdlib.h>
#include<immintrin.h>

void main(void)
{
    float a[8] = {.1,.2,.3,.4,.5,.6,.7,.8};
    float b[8] = {.8,.7,.6,.5,.4,.3,.2,.1};
    float c[8] = {.5,.4,.5,.4,.5,.4,.5,.4};
    float d[8] = {0,0,0,0,0,0,0,0};

    struct timespec start,end;

    clock_gettime(CLOCK_REALTIME,&start);
    for(int i=0;i<100000000;i++)
    {
        d[0] = a[0]*b[0]+c[0];
        d[1] = a[1]*b[1]+c[1];
        d[2] = a[2]*b[2]+c[2];
        d[3] = a[3]*b[3]+c[3];
        d[4] = a[4]*b[4]+c[4];
        d[5] = a[5]*b[5]+c[5];
        d[6] = a[6]*b[6]+c[6];
        d[7] = a[7]*b[7]+c[7];
    }
    clock_gettime(CLOCK_REALTIME,&end);
    printf("32bit elapsed time (sec) : %.9f\n", (end.tv_sec - start.tv_sec) + (double)(end.tv_nsec - start.tv_nsec)/1000000000);
}

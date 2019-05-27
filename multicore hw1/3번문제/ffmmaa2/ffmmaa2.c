#include<stdio.h>
#include<time.h>
#include<math.h>
#include<stdlib.h>
#include<immintrin.h>

void main(void)
{
    __m256 a = _mm256_set_ps(.1,.2,.3,.4,.5,.6,.7,.8);
    __m256 b = _mm256_set_ps(.8,.7,.6,.5,.4,.3,.2,.1);
    __m256 c = _mm256_set_ps(.5,.4,.5,.4,.5,.4,.5,.4);
    __m256 d = _mm256_set_ps(0,0,0,0,0,0,0,0);

    struct timespec start,end;

    clock_gettime(CLOCK_REALTIME,&start);
    for(int i=0;i<100000000;i++)
    {
        d = _mm256_fmadd_ps(a,b,c);
    }
    clock_gettime(CLOCK_REALTIME,&end);
    printf("32bit elapsed time (sec) : %.9f\n", (end.tv_sec - start.tv_sec) + (double)(end.tv_nsec - start.tv_nsec)/1000000000);
}

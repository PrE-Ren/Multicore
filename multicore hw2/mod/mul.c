
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
//#include <immintrin.h>
//#include <time.h>
//====================================================================
// a[N][M] x b[M][N] = c[N][N]
//====================================================================

typedef struct tdata
{
 float *a;
 float *b;
 float *c;
 int n;
 int m;
 int lnum;
 int size;
}dat;

void *mul(void *line)
{
  dat* x = (dat*)line;
  int perthr,tmp;
  int n = x->n;
  int m = x->m;
  float *a = x->a;
  float *b = x->b;
  float *c = x->c;
  //struct timeval t1,t2;
  perthr = n/(x->size);
  tmp = (x->lnum)*perthr;
  for(int i=tmp;i<tmp+perthr;i++){
    for(int k=0;k<n;k++){
      for(int j=0;j<m;j++){
        /*__m256 a1 = _mm256_load_ps(&a[i*m+k]);
        __m256 b1 = _mm256_set_ps(b[k*n+j],b[(k+1)*n+j],b[(k+2)*n+j],b[(k+3)*n+j],b[(k+4)*n+j],b[(k+5)*n+j],b[(k+6)*n+j],b[(k+7)*n+j]);
        __m256 c1 = _mm256_set_ps(0,0,0,0,0,0,0,0);
        float *d = (float*)malloc(sizeof(float)*8); */
        c[i*n+j] += a[i*m+k] * b[k*n+j];
        //_mm256_store_ps(d,_mm256_fmadd_ps(a1,b1,c1));
        //float stor = 0;
        //for(int y=0;y<8;y++)
        //{
         // stor = d[y];
        //}
        //c[i*n+j] = stor;
      }
    }
  }
  return NULL;
}
void mat_mul(float *a, float *b, float *c, int N, int M) {
  int num = 16;
  //printf("Input number of threads:");
  //scanf("%d",&num);
  pthread_t *pt = (pthread_t *)malloc(sizeof(pthread_t)*num);
  for(int i=0;i<num;i++)
  {
    dat *tdat = (dat *)malloc(sizeof(dat));
    tdat->a = a;
    tdat->b = b;
    tdat->c = c;
    tdat->n = N;
    tdat->m = M;
    tdat->lnum = i;
    tdat->size = num;
    pthread_create(&pt[i],NULL,mul,(void*)tdat);
  }
  for(int j=0;j<num;j++)
  {
    pthread_join(pt[j],NULL);
  }
}

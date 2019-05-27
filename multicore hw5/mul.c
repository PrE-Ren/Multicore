#include <omp.h>
#include <mpi.h>

//====================================================================
// a[N][M] x b[M][N] = c[N][N]
//====================================================================
void mat_mul(float *a, float *b, float *c, int N, int M) {  
  omp_set_num_threads(32);
  int rank, size;
  MPI_Comm_size(MPI_COMM_WORLD, &size);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  int lpn = N/size;
  if(rank == 0)
  {
    for(int i=1;i<size;i++)
    {
      MPI_Send(a+i*M*lpn,M*lpn,MPI_FLOAT,i,1000,MPI_COMM_WORLD);
      MPI_Send(b,M*N,MPI_FLOAT,i,1000,MPI_COMM_WORLD);
    }

    for (int i = 0; i < lpn; i++) {
      for (int j = 0; j < N; j++) {
        c[i * N + j] = 0;
      }
    }

    #pragma omp parallel for
    for (int i = 0; i < lpn; i++) {
      for (int k = 0; k < M; k++) {
        for (int j = 0; j < N; j++) {
          c[i * N + j] += a[i * M + k] * b[k * N + j];
        }
      }
    }

    for(int i=1;i<size;i++)
    {
      MPI_Recv(c+i*lpn*N,lpn*N,MPI_FLOAT,i,1001,MPI_COMM_WORLD,NULL);
    }
  }
  else
  {
    for (int i = 0; i < lpn; i++) {
      for (int j = 0; j < N; j++) {
        c[i * N + j] = 0;
      }
    }
    MPI_Recv(a,lpn*M,MPI_FLOAT,0,1000,MPI_COMM_WORLD,NULL);
    MPI_Recv(b,M*N,MPI_FLOAT,0,1000,MPI_COMM_WORLD,NULL);
    #pragma omp parallel for
    for (int i = 0; i < lpn; i++) {
      for (int k = 0; k < M; k++) {
        for (int j = 0; j < N; j++) {
          c[i * N + j] += a[i * M + k] * b[k * N + j];
        }
      }
    }
    MPI_Send(c,lpn*N,MPI_FLOAT,0,1001,MPI_COMM_WORLD);
  }
}

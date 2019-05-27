#define BLOCK_SIZE 16

__kernel void mat_mul(__global float *A, __global float *B, __global float *C, int N, int M)
{
  int i = get_group_id(1); // row
  int j = get_group_id(0); // col
  
  int x = get_local_id(1);
  int y = get_local_id(0);

  int num = N/BLOCK_SIZE;
  __local float tmpA[BLOCK_SIZE][BLOCK_SIZE];
  __local float tmpB[BLOCK_SIZE][BLOCK_SIZE];
  //float acc = 0;
  float4 acc = {0,0,0,0};
  for(int k=0;k<num;k++)
  {
    tmpA[x][y] = A[M*(BLOCK_SIZE*i+x) + BLOCK_SIZE*k+y];
    tmpB[x][y] = B[N*(BLOCK_SIZE*k+x) + BLOCK_SIZE*j+y];
    barrier(CLK_LOCAL_MEM_FENCE);
    for(int l=0;l<BLOCK_SIZE;l+=4)
    {
      float4 a = {tmpA[x][l],tmpA[x][l+1],tmpA[x][l+2],tmpA[x][l+3]};
      float4 b = {tmpB[l][y],tmpB[l+1][y],tmpB[l+2][y],tmpB[l+3][y]};
      acc += a*b;
      //acc += tmpA[x][l] * tmpB[l][y];
    }
    barrier(CLK_LOCAL_MEM_FENCE);
  }
  C[M*(BLOCK_SIZE*i+x) + BLOCK_SIZE*j+y] = acc.x+acc.y+acc.z+acc.w;
}

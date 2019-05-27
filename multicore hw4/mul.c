#include <stdio.h>
#include <stdlib.h>
#include <CL/cl.h>
#include <unistd.h>
#include <string.h>
#define GPUS 4
//====================================================================
// a[N][M] x b[M][N] = c[N][N]
//====================================================================

cl_context context;
cl_program program;
cl_kernel kernel[GPUS];
cl_command_queue command_queue[GPUS];
cl_mem bufA[GPUS],bufB,bufC[GPUS];
int pieces;

char *get_source_code(const char *file_name, size_t *len)
{
  char *result;
  size_t length;
  FILE *file = fopen(file_name,"r");
  fseek(file,0,SEEK_END);
  length = (size_t)ftell(file);
  rewind(file);
  result = (char*)malloc(length+1);
  fread(result,length,1,file);
  result[length] = '\0';
  fclose(file);
  *len = length;
  return result;
}

const char* kernel_src = 
"__kernel void zero(__global float *A, __global float *B, __global float *C, const int N, const int M){"
"const int row = get_global_id(0);"
"const int col = get_global_id(1);"
"float acc = 0.0f;"
"for(int k=0;k<M;k++){"
"  acc += A[row*M+k]*B[k*N+col];"
"}"
"C[N*row+col] = acc;"
"}";


void mat_mul(float *a, float *b, float *c, int N, int M) {
  /*for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) {
      for (int k = 0; k < M; k++) {
        c[i * N + j] += a[i * M + k] * b[k * N + j];
      }
    }
  }*/
  size_t global_size[2] = {N,N/GPUS};
  size_t local_size[2] = {16,16};

  for(int x=0;x<GPUS;x++)
  {
    //printf("%f %f \n", *a, *(a+x*M*pieces));
    clEnqueueWriteBuffer(command_queue[x],bufA[x],CL_FALSE,0,sizeof(float)*M*pieces,&(a[x*M*pieces]),0,NULL,NULL);
    clEnqueueWriteBuffer(command_queue[x],bufB,CL_FALSE,0,sizeof(float)*M*N,b,0,NULL,NULL);
    clEnqueueNDRangeKernel(command_queue[x],kernel[x],2,NULL,global_size,local_size,0,NULL,NULL);
  }

  for(int x=0;x<GPUS;x++)
    clEnqueueReadBuffer(command_queue[x],bufC[x],CL_TRUE,0,sizeof(float)*N*pieces,&(c[x*N*pieces]),0,NULL,NULL);
  /*clReleaseMemObject(bufA);
  clReleaseMemObject(bufB);
  clReleaseMemObject(bufC);
  clReleaseKernel(kernel);
  clReleaseProgram(program);
  clReleaseCommandQueue(command_queue);
  clReleaseContext(context);*/
}
void setup(int N, int M) {
  /* do some runtime setup here */  
  cl_platform_id platform;
  clGetPlatformIDs(1, &platform, NULL);
  pieces = N/GPUS;
  cl_device_id device[GPUS];
  clGetDeviceIDs(platform, CL_DEVICE_TYPE_GPU,GPUS, device, NULL);
  context = clCreateContext(0,GPUS,device,NULL,NULL,NULL);
  for(int x=0;x<GPUS;x++)
    command_queue[x] = clCreateCommandQueue(context,device[x],0,NULL);

  char *kernel_source;
  size_t kernel_source_size; //= strlen(kernel_src);
  kernel_source = get_source_code("kernel.cl",&kernel_source_size);
  program = clCreateProgramWithSource(context,1,(const char**) &kernel_source, &kernel_source_size, NULL);
  clBuildProgram(program,GPUS,device,NULL,NULL,NULL);
  
  bufB = clCreateBuffer(context,CL_MEM_READ_ONLY,sizeof(float)*M*N,NULL,NULL);
  
  for(int x=0;x<GPUS;x++)
  {
    kernel[x] = clCreateKernel(program,"mat_mul",NULL);

    bufA[x] = clCreateBuffer(context,CL_MEM_READ_ONLY,sizeof(float)*M*pieces,NULL,NULL);
    bufC[x] = clCreateBuffer(context,CL_MEM_WRITE_ONLY,sizeof(float)*N*pieces,NULL,NULL);
    clSetKernelArg(kernel[x],0,sizeof(cl_mem), (void*) &(bufA[x]));
    clSetKernelArg(kernel[x],1,sizeof(cl_mem), (void*) &bufB);
    clSetKernelArg(kernel[x],2,sizeof(cl_mem), (void*) &(bufC[x]));
    clSetKernelArg(kernel[x],3,sizeof(cl_int), (void*) &pieces);
    clSetKernelArg(kernel[x],4,sizeof(cl_int), (void*) &M);
    clSetKernelArg(kernel[x],5,sizeof(cl_int), (void*) &N);
  }
}

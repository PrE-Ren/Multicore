#include <stdio.h>
#include <stdlib.h>
#include <CL/cl.h>
#include <unistd.h>
#include <string.h>
//====================================================================
// a[N][M] x b[M][N] = c[N][N]
//====================================================================

cl_context context;
cl_program program;
cl_kernel kernel;
cl_command_queue command_queue;
cl_mem bufA,bufB,bufC;

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
  clEnqueueWriteBuffer(command_queue,bufA,CL_FALSE,0,sizeof(float)*M*N,a,0,NULL,NULL);
  clEnqueueWriteBuffer(command_queue,bufB,CL_FALSE,0,sizeof(float)*M*N,b,0,NULL,NULL);
  size_t global_size[2] = {N,N};
  size_t local_size[2] = {16,16};
  clEnqueueNDRangeKernel(command_queue,kernel,2,NULL,global_size,local_size,0,NULL,NULL);
  clEnqueueReadBuffer(command_queue,bufC,CL_TRUE,0,sizeof(float)*N*N,c,0,NULL,NULL);
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
  cl_device_id device;
  clGetDeviceIDs(platform, CL_DEVICE_TYPE_GPU,1, &device, NULL);
  context = clCreateContext(0,1,&device,NULL,NULL,NULL);
  command_queue = clCreateCommandQueue(context,device,0,NULL);
  char *kernel_source;
  size_t kernel_source_size; //= strlen(kernel_src);
  kernel_source = get_source_code("kernel.cl",&kernel_source_size);
  program = clCreateProgramWithSource(context,1,(const char**) &kernel_source, &kernel_source_size, NULL);
  clBuildProgram(program,1,&device,NULL,NULL,NULL);
  kernel = clCreateKernel(program,"mat_mul",NULL);
  bufA = clCreateBuffer(context,CL_MEM_READ_ONLY,sizeof(float)*M*N,NULL,NULL);
  bufB = clCreateBuffer(context,CL_MEM_READ_ONLY,sizeof(float)*M*N,NULL,NULL);
  bufC = clCreateBuffer(context,CL_MEM_WRITE_ONLY,sizeof(float)*N*N,NULL,NULL);
  clSetKernelArg(kernel,0,sizeof(cl_mem), (void*) &bufA);
  clSetKernelArg(kernel,1,sizeof(cl_mem), (void*) &bufB);
  clSetKernelArg(kernel,2,sizeof(cl_mem), (void*) &bufC);
  clSetKernelArg(kernel,3,sizeof(cl_int), (void*) &N);
  clSetKernelArg(kernel,4,sizeof(cl_int), (void*) &M);
}

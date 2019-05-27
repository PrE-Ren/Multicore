CC_SIMD = gcc
CC_CUDA = nvcc

SIMD = simd
CUDA = cuda

NDIM = 2048
MDIM = 2048
EXE_OPTION = 
#EXE_OPTION = -v

all: $(SIMD) $(CUDA)

$(SIMD): mat_mul_simd.c
	$(CC_SIMD) -o $@ $^ -std=c99 -mavx -Wall -lm

$(CUDA): mat_mul_cuda.cu
	$(CC_CUDA) -o $@ $^ -Wno-deprecated-gpu-targets -lm

.PHONY: clean runsimd runcuda

clean:
	rm -rf *.o $(SIMD) $(CUDA)

runsimd: $(SIMD)
	@thorq --add --mode single --device cpu --timeout 60 ./$< $(NDIM) $(MDIM) $(EXE_OPTION)

runcuda: $(CUDA)
	@thorq --add --mode single --device gpu/1080 --timeout 60 ./$< $(NDIM) $(MDIM) $(EXE_OPTION)

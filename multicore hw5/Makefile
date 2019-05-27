CC = mpicc
TARGET = mat_mul
OBJECTS = main.o mul.o timer.o

CFLAGS = -std=c11 -Wall -fopenmp
LDFLAGS = -lm -fopenmp

MODE = mpi
DEVICE = cpu
NODES = 4
SLOTS = 1

NDIM = 4096
MDIM = 4096
EXE_OPTION =
#EXE_OPTION = -v

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) -o $@ $^ $(LDFLAGS)

.PHONY: clean run

clean:
	rm -rf $(TARGET) $(OBJECTS)

run: $(TARGET)
	@thorq --add --mode $(MODE) --nodes $(NODES) --slots $(SLOTS) --device $(DEVICE) \
	 ./$(TARGET) $(NDIM) $(MDIM) $(EXE_OPTION)

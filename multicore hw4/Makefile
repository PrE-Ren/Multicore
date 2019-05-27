CC = gcc
TARGET = mat_mul
OBJECTS = main.o mul.o timer.o

CFLAGS = -std=c11 -Wall
LDFLAGS = -lm -lOpenCL

MODE = single
DEVICE = gpu/7970

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
	@thorq --add --mode $(MODE) --device $(DEVICE) --timeout 60 ./$(TARGET) $(NDIM) $(MDIM) $(EXE_OPTION)

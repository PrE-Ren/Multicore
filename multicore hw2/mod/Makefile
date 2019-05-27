CC = gcc
TARGET = mat_mul
OBJECTS = main.o mul.o timer.o

CFLAGS = -std=c99 -Wall
LDFLAGS = -lm

MODE = single
DEVICE = cpu

NDIM = 2048
MDIM = 2048

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) -mavx2 -mfma -pthread -o $@ $^ $(LDFLAGS)

.PHONY: clean run

clean:
	rm -rf $(TARGET) $(OBJECTS)

run: $(TARGET)
	@thorq --add --mode $(MODE) --device $(DEVICE) --timeout 60 ./$(TARGET) $(NDIM) $(MDIM) -v

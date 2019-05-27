float.o : float.c
	gcc -c float.c

float : float.o
	gcc -o float float.o

run : float
	./float

clean:
	rm -f float float.o
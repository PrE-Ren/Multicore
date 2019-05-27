double.o : double.c
	gcc -c double.c

double : double.o 
	gcc -o double double.o 

run : double
	./double

clean:
	rm -f double double.o
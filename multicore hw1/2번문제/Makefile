flopflop.o : flopflop.c
	gcc -c flopflop.c

flopflop : flopflop.o 
	gcc -o flopflop flopflop.o 

run : flopflop
	./flopflop

clean:
	rm -f flopflop flopflop.o
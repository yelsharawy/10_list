all: main.o
	gcc -o list main.o

main.o: main.c
	gcc -c main.c

clean:
	-rm ./*.o
	-rm ./list*

run:
	./list*

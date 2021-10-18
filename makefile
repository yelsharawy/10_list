all: main.o personlist.o
	gcc -o list main.o personlist.o

main.o: main.c personlist.h
	gcc -c main.c

personlist.o: personlist.c personlist.h
	gcc -c personlist.c

clean:
	-rm ./*.o
	-rm ./list*

run:
	./list*

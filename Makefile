CC = clang -g -Wall
all: main test


%.o: %.c %.h
	$(CC) -c $<

intersection.o: intersection.c intersection.h macros.h
territory.o: territory.c territory.h macros.h intersection.h grid.h
main.o: main.c territory.h grid.h macros.h
grid.o: grid.c grid.h macros.h 
test.o: test.c grid.h macros.h territory.h intersection.h


main: main.o territory.o grid.o intersection.o 
	$(CC) $^ -o $@

test: test.o territory.o grid.o intersection.o
	$(CC) $^ -o $@

clean:
	rm -f $(all) *.o

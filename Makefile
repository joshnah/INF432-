CC = clang -g -Wall
all: main


%.o: %.c %.h
	$(CC) -c $<

territory.o: territory.c territory.h
main.o: main.c territory.h grid.h
grid.o: grid.c grid.h

main: main.o territory.o grid.o
	$(CC) $^ -o $@

clean:
	rm -f $(all) *.o

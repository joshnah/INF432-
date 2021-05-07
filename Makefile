# Compilator
CC = clang -g -Wall

# Executables
EXECUTABLES = main sat3 generate_test_max walksat generate_random_grid

all : $(EXECUTABLES);

########################################################
#   COMPILATION OF MODULES 
########################################################



%.o: %.c %.h
	@echo ""
	@echo "---------------------------------------------"
	@echo "Compilation of modules "$*
	@echo "---------------------------------------------"
	$(CC) -c $<
	@echo ""

intersection.o: intersection.c intersection.h macros.h

territory.o: territory.c territory.h macros.h intersection.h grid.h

main.o: main.c territory.h grid.h macros.h

grid.o: grid.c grid.h macros.h 

macros.o: macros.c macros.h

rules.o: rules.c rules.h territory.h grid.h

test.o: test.c grid.h macros.h territory.h intersection.h

sat3.o: sat3.c

generate_test_max.o: generate_test_max.c

clause.o: clause.c clause.h

walksat.o: walksat.c clause.h 

generate_random_grid.o: generate_random_grid.c

########################################################
# 	LINKING OBJECT FILES
########################################################
main: main.o territory.o grid.o intersection.o macros.o rules.o
	$(CC) $^ -o $@

test: test.o territory.o grid.o intersection.o macros.o
	$(CC) $^ -o $@

sat3: sat3.o
	$(CC) $^ -o $@

generate_test_max: generate_test_max.o
	$(CC) $^ -o $@

walksat: walksat.o clause.o
	$(CC) $^ -o $@

generate_random_grid: generate_random_grid.o
	$(CC) $^ -o $@

########################################################
#	Clean folder
########################################################

	
clean:
	rm -fR $(EXECUTABLES) *.o *.cnf picosat result_walksat.txt max_input.txt
	rm -f ./picosat-965/picosat ./picosat-965/picomcs ./picosat-965/picomus ./picosat-965/picogcnf
	rm -f ./picosat-965/*.exe ./picosat-965/*.s ./picosat-965/*.o ./picosat-965/*.a ./picosat-965/*.so ./picosat-965/*.plist
	rm -f ./picosat-965/makefile ./picosat-965/config.h
	rm -f ./picosat-965/gmon.out ./picosat-965/*~


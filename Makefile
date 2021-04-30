# Compilator
CC = clang -g -Wall

# Executables
EXECUTABLES = main sat3 generate_test_max walksat

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


########################################################
#	Clean folder
########################################################

	
clean:
	rm -fR $(EXECUTABLES) *.o *.cnf picosat
	rm -f picosat picomcs picomus picogcnf
	rm -f *.exe *.s *.o *.a *.so *.plist
	rm -f makefile config.h
	rm -f gmon.out *~


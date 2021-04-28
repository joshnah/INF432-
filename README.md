- Command to compile: make

<!-- EXECUTABLE -->

./main <name of input file> <flags>

d : display information
s : convert to output3sat.cnf and use our walksat solver to solve it

<!-- By default, we only use picosat to solve -->
<!-- EXAMPLE -->


-   ./main input.txt
    <!-- The program will only return the result by picosat -->

-   ./main input.txt d
    <!-- The program will display territories information and return the result by picosat -->

-   ./main input.txt ds 
    <!-- The program will display territories information and return the result by picosat and our walksat -->
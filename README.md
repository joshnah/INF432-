<!-- COMMAND TO BEGIN -->

        ./config.sh

<!-- INPUT FORMAT -->



 First line: N Dimension of the grid.
 Second line: T Number of territory.
 For the next T lines: "b x y" where b is the number of bomb and (x,y) is the coordinate of the marked box.
 
 # The order of territories needs to be from top to bottom, left to right
 # Two territories with same marked box will raise an error


 #### Example ####
 4
 3
 2 1 1
 3 2 3
 0 3 4


 This input file contains a grid of dimension 4 x 4, with 3 territories:
 + Territory with 2 bombs marked at (1,1)
 + Territory with 3 bombs marked at (2,3)
 + Territory with 0 bombs marked at (3,4)

<!-- EXECUTABLE -->

./main <name of input file> <flags>

d : display information
s : convert to output3sat.cnf and use our walksat solver to solve it

<!-- By default, we only use picosat to solve -->

#### Example ####

-   ./main input.txt
    <!-- The program will only return the result by picosat -->

-   ./main input.txt d
    <!-- The program will display territories information and return the result by picosat -->

-   ./main input.txt ds 
    <!-- The program will display territories information and return the result by picosat and our walksat -->


<!-- GENERATION OF MAX INPUT  -->
This program will generate a grid of maximum territories and bombs in input.txt

    ./generate_test_max <dimension>


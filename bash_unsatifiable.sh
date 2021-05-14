#!/bin/bash
#BASH PROGRAM TO EXECUTE ALL THE UNSATIFIABLES TEST CASES
for f in ./test_cases/unsatifiable/*
do
	printf "Test file: "
	echo $f
	printf "\n"
	cat $f
	printf "\n"
	./main $f 
	printf "\n******************\n\n"

done



#!/bin/bash
#BASH PROGRAM TO EXECUTE ALL THE EXTREME TEST CASES

for f in ./test_cases/extreme/*
do
	printf "Test file: "
	echo $f
	printf "\n"
	cat $f
	printf "\n"
	./main $f
	printf "\n******************\n\n"

done



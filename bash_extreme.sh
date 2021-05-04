#!/bin/bash
for f in ./test_cases/extreme/*
do
	printf "Test file: "
	echo $f
	printf "\n"
	./main $f
	printf "\n******************\n\n"

done



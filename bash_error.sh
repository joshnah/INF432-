#!/bin/bash
for f in ./test_cases/error_input/*
do
	printf "Case error: "
	echo $f
	printf "\n"
	cat $f
	printf "\n"
	./main $f s
	printf "\n******************\n\n"

done



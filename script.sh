#!/bin/bash

DIRECTORY=maps_test
OK='\033[092m[ OK ]\033[0m'
KO='\033[091m[ KO ]\033[0m'


get_error()
{
	RET=$?
	if (( $RET == $((128 + 6)) )); then
		echo -e "\033[091m[ ABRT ]\033[0m"
	elif (( $RET == $((128 + 10)) )); then
		echo -e "\033[091m[ BUS ]\033[0m"
	elif (( $RET == $((128 + 11)) )); then
		echo -e "\033[091m[ SEGV ]\033[0m"
	else
		echo -e $OK
	fi
}

DIR=$(find $DIRECTORY -type d)
for subdir in $DIR
do
	printf "\033[94m\n%s\n\n\033[0m" $subdir
	for file in $subdir/*
	do
		if [ -f "$file" ]; then
		printf "%-20s" ${file##*/}
		if ./lem-in < $file >&/dev/null; then true; else get_error; fi 2> /dev/null
		fi
	done
done



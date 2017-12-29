#!/bin/bash

DIRECTORY=maps_ok
PATH_LEMIN=../
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
	elif (( $RET == $((128 + 4)) )); then
		echo -e "\033[091m[ ILL ]\033[0m"
	elif (( $RET == $((128 + 8)) )); then
		echo -e "\033[091m[ FPE ]\033[0m"
	elif (( $RET == $((128 + 13)) )); then
		echo -e "\033[091m[ PIPE ]\033[0m"
	else
		echo -e $KO
	fi
}

DIR=$(find $DIRECTORY -type d)
for subdir in $DIR
do
	if [ "$(find $subdir -type f -maxdepth 1)" ]; then
		printf "\033[94m\n%s\n\n\033[0m" ${subdir##*/}
	fi
	for file in $subdir/*
	do
		if [ -f "$file" ]; then
		printf "%-20s" ${file##*/}
		if $PATH_LEMIN./lem-in < $file >&/dev/null; then echo -e $OK; else get_error; fi 2> /dev/null
		fi
	done
done



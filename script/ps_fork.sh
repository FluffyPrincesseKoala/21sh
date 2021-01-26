#!/bin/bash
clear
nb=0
new=""
old=0	
while true
do
	new="$(ps -aux | grep ./21sh)"
	nb="$(printf "$new" | wc -l)"
	if [ "$nb" != "$old" ]
	then
		clear
	 	printf "\033[38;5;50m USER\t PID\tCPU  MEM  VSZ\t  RSS\tTTY STAT    TIME   OSEF CMD \033[0m \n"
		printf "$new\n"
	fi
	old="$(printf "$new" | wc -l)"
	new=""
done
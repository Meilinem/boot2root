#!/bin/bash

i=1
passwd=""
tmp=""
search=""

if [[ "$1" == "-h" || "$1" == "--help" ]]; then
	printf "bash launch_me.sh"
	echo " [-v verbose]"
	exit
fi

while (( i < 13 )); do
	if (( i >= 8 )); then
		letter=$(echo $(grep -H -a2 "char getme$i" ft_fun/* | awk -F "return \'" '{print $2}') | awk -F "\';" '{print $1}')
		tmp=$(grep -H "char getme$i" ft_fun/* | awk -F "ft_fun/" '{print $2}' | awk -F ".pcap" '{print $1}')
		if [[ "$1" == "-v" ]]; then
			file=$tmp
			printf "Directly found :\n"
			printf "\tFound in file \033[94;1m$file.pcap\033[0m for \033[94;1mgetme%-3d\033[0m: \033[31;1m$letter\033[0m\n\n" $i
		fi
		passwd+=$letter
	else
		tmp=$(grep -a2 "char getme$i" ft_fun/* | awk -F "//file" '{print $2}')
		file=$(echo $(grep -H "char getme$i" ft_fun/* | awk -F "ft_fun/" '{print $2}') | awk -F ".pcap" '{print $1}')
		if [[ "$1" == "-v" ]]; then
			printf "Found in file \033[94;1m$file.pcap\033[0m for \033[94;1mgetme%-3d\033[0m:\n" $i
			printf "\--> asks us to go \033[32;1m//file$((tmp+1))\033[0m\n"
		fi
		search=$(echo $(grep -a3w "//file$((tmp+1))" ft_fun/* | awk -F "return \'" '{print $2}') | awk -F "\';" '{print $1}')
		if [[ "$1" == "-v" ]]; then
			file=$(echo $(grep -a3Hw "//file$((tmp+1))" ft_fun/* | awk -F "ft_fun/" '{print $2}') | awk -F ".pcap" '{print $1}')
			printf "\tFound in file \033[94;1m$file.pcap \033[0mfor \033[94;1mgetme%-3d\033[0m: \033[31;1m$search\033[0m\n\n" $i
		fi

		passwd+=$search
	fi
	let i++
done

printf "A password had been scanned: \033[32;1m$passwd\033[0m\n"

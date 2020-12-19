#!/bin/bash
txt="
Public speaking is very easy.
1 2 6 24 120 720
1 b 214
9
opekmq
4 2 6 3 1 5
"

touch answers && echo "$txt" > answers && chmod 777 answers

logs=`./bomb < answers`

touch bomb.log && echo "$logs" > bomb.log && chmod 777 bomb.log
head=$(head -n 2 bomb.log)
head=$(echo $head | sed 's/\n/ /')
sed -i '1,2d' bomb.log
echo -e "$head\n$(cat bomb.log)" > bomb.log

while true
do
  read -r f1 <&3 || break
  read -r f2 <&4 || break
  if [[ ! -z $f1 ]]; then
  	printf '$>\033[94;1m %s\033[0m\n' "$f1"
  fi

  if [[ ! -z $f2 ]]; then
	if [[ $f2 == *"Congratulations!"* ]]; then
  		printf '\n\033[31;1m%s\033[0m\n' "$f2"
	else
  		printf '\n\033[32;1m%s\033[0m\n' "$f2"
	fi
  fi
done 3<answers 4<bomb.log

rm answers
rm bomb.log

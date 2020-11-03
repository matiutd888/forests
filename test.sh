#!/bin/bash

if [ $# -lt 2 ]; then
    echo "Za mało argumentów!"
    exit 1
fi


wyniki=$(mktemp -d wynikiXXXXXXXXXXXX)

k=0
j=0
i=0

prog=$1

for f in "${2}"/*.in
do

  if ! valgrind --error-exitcode=15 --leak-check=full \
  --show-leak-kinds=all --errors-for-leak-kinds=all --log-file=/dev/null \
   $(dirname ${prog})/$(basename ${prog})  <$f \
    >$wyniki/$(basename -- ${f%in}out) 2>$wyniki/$(basename -- ${f%in}err); 
   then
		ProblemyZPamiecia[k]="$(basename -- $f)"
		((k++));
   fi;
  
  if diff ${f%in}err $wyniki/$(basename -- ${f%in}err) >/dev/null && \
		diff ${f%in}out $wyniki/$(basename -- ${f%in}out) >/dev/null; 
	then
		echo "$(basename -- $f) pliki OK!"
		DobreTesty[j]="$(basename -- $f)"
		((j++));
	else
		echo "$(basename -- $f) ERROR!"
		
		ZleTesty[i]="$(basename -- $f)"
		((i++));
	fi;
done


rm -r $wyniki

echo ""
if [ ${#ZleTesty[@]} -eq 0 ]; then
	echo "Wszystkie pliki OK!";
else 
	echo "Dobre wyniki dla testów: "
	for i in "${DobreTesty[@]}"; do echo "$i"; done
	
	echo ""
	echo "złe wyniki dla testów: "
	for i in "${ZleTesty[@]}"; do echo "$i"; done;
fi;

echo ""
if [ ${#ProblemyZPamiecia[@]} -eq 0 ]; then
	echo "Brak problemów z pamięcią!";
else 
	echo "problemy z pamięcią wykryte dla testów: "
	for i in "${ProblemyZPamiecia[@]}"; do echo "$i"; done;
fi;

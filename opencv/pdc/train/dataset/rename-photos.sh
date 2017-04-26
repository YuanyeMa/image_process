#!/bin/bash

#usage $./rename-photos path extesion_name
#example $ ./rename-photos.sh ~/Picture/2012-11-25 jpg

path=${1:-$(pwd)}
#echo $path

if echo $path | grep ".*/$" > /dev/null
then 
	length=$(expr length $path)
	length=$((length-1))
	path=$(expr substr $path 1 $length)
fi

foldrname=${path##/*/}
#echo $foldrname
ext=${2:-"jpg"}

pics=$(ls $path/*.$ext | sed 's/ //g') #  is CTRL+Z

i=1
for p in $pics
do
	old_name=$(echo $p | sed 's//\ /g')
	new_name=$(printf "%s/%s_%d.%s\n" $path $foldrname $i $ext)
	echo $new_name
	echo mv "$old_name" "$new_name"
	mv "$old_name" "$new_name"
	echo $((i+=1)) > /dev/null
done

exit 0




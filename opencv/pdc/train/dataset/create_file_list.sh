#!/bin/bash
creat_list() {
	ls ./pos > pos_sample_list.txt
	wc -l ./pos_sample_list.txt
	ls ./neg > neg_sample_list.txt
	wc -l ./neg_sample_list.txt

	HARD_FILE=`ls ./hard/ | wc -l`
	if [  $HARD_FILE ] ; then
		ls  ./hard/  > hard_sample_list.txt
		wc -l ./hard_sample_list.txt
	fi

	ORI_NEG_FILE=`ls ./neg_ori/ | wc -l`
	if [  $ORI_NEG_FILE ] ; then
		ls  ./neg_ori/  > ori_neg_sample_list.txt
		wc -l ./ori_neg_sample_list.txt
	fi
}

clear_list() {
	rm -rf ./*.txt
}


if [ $# != 1 ] ; then 
	echo "Usage : ./create_sample_list.sh create/clear" 
	exit
fi

if [ $1 == "create" ] ; then 
	creat_list
elif [ $1 == "clear" ] ; then 
	clear_list
else  
	echo "Usage : ./create_sample_list.sh create/clear" 
	exit
fi



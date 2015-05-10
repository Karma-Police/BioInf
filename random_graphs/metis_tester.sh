#!/bin/bash

if [ $# -ne 4 ]
then
  echo "Wrong arguments!"
  echo "Usage: script_name [tests_count] [graph_size] [clusters_count] [random par (integer from 1 to 999) ]"
  exit 0
fi

for (( i = 0; i < $1; i++ )); do
  echo "processing..."
  ./get_test $2 $3 $4 &> ./test.extr_info
  gpmetis ./test.in $3 &> /dev/null
  mv ./test.in.part.$3 ./metis.out
  ./successor >> ./logfile
  echo $i tests over 
done

./logparser
echo '' > ./logfile


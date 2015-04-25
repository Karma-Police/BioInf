#!/bin/bash

if [ $# -ne 4 ]
then
  echo "Wrong arguments!"
  echo "Usage: script_name [tests_count] [graph_size] [clusters_count] [random par (integer from 1 to 99) ]"
  exit 0
fi

for (( i = 0; i < $1; i++ )); do
  echo "fuck"
  ./get_test $2 $3 $4 &> ./test.extr_info
  gpmetis ./test.in.part.$3 &> /dev/null
  ./successor >> ./logfile
done

./logparser


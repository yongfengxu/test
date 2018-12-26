#!/bin/bash
while true
do
  time=$(date "+%Y-%m-%d %H:%M:%S")
  echo -e "\n\n\n" + $time + "\n\n\n" 
  expect show.exp
  sleep 1
done

#!/bin/bash

perl_path=`which perl`

if [ -z $perl_path ]
then 
  echo -n "Please install perl!"
fi

if [ "$#" -eq "1" ]
then
  installation_path=$1
else
	echo -n "Please give me the installation path: "
	read -e installation_path
fi



$perl_path ./setBaseDir.pl ./ $installation_path
./builder.sh -install
./builder.sh -clean


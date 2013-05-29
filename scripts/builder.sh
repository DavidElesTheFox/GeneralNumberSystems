#!/bin/bash

MAKE_FILE_TYPE="Unix Makefiles"
if [ "$#" -gt "1" ]
then
  MAKE_FILE_TYPE="$2"
fi

function clean()
{
	local projectName=$1;
	if [ -d $projectName ]
	then
		cd $projectName
		if [ -d "build" ]
		then
			echo -e "\t\e[0;31mDELETE \e[0;32m$PWD/build\e[0m"
      rm -r build
			mkdir build
		fi
		ls > tmp
		while read line
		do
			if [ -d $line ] && [ "$line" != "header" ] && [ "$line" != "source" ] && [ "$line" != "lib" ]
			then
        clean $line
			fi
		done < tmp
		rm tmp
		cd ..
	fi
}

function install
{
	local projectName=$1
	if [ -d $projectName ]
	then
		cd $projectName
		if [ -d "build" ]
		then
			cd build
			echo -e "\t\e[0;31mINSTALL \e[0;32m$PWD/build\e[0m"
			cmake -G "$MAKE_FILE_TYPE" ../
			make install
			cd ..
		fi
		ls > tmp
		while read line
		do
			if [ -d $line ] && [ "$line" != "header" ] && [ "$line" != "source" ] && [ "$line" != "lib" ] && [ "$line" != "test" ] && [ "$line" != "Test" ] && [ "$line" != "doc" ]
			then
				install $line
			fi
		done < tmp
	  rm tmp
		cd ..
	fi
}

function clean_all
{
	clean MATH
	clean Exceptions
	clean Graphics
	clean Logger
	clean NET
	clean StringUtil
	clean Tester
}

function install_all
{
	install Exceptions
	install Logger
	install Tester
	install MATH
	install StringUtil
	install NET
	install Graphics
}

if [ "$1" == "-install" ]
then
  install_all
elif [ "$1" == "-clean" ]
then
  clean_all
else
  echo -e 'usage: builder.sh [-install|-clean] ["Make file type"]'
fi
#




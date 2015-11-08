#!/bin/bash
PATH=/bin:/sbin:/usr/bin:/usr/sbin:/usr/local/bin:/usr/local/sbin:~/bin
export PATH

#domain=http://www.imly.org

while read -r dir200
	do
		urltocheck=$1$dir200
		linkchecker --verbose $urltocheck > filesforinput/in.txt
		echo $urltocheck | ./generate_urllist
	done < filesforinput/dirs_200.txt

while read -r file200
	do
		filetoappend=$1$file200
		echo $filetoappend >> urllist.txt
	done < filesforinput/files.txt


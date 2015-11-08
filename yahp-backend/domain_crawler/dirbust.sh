#!/bin/bash
PATH=/bin:/sbin:/usr/bin:/usr/sbin:/usr/local/bin:/usr/local/sbin:~/bin
export PATH
 

if [ -f Dirbuster_report/report.txt ];
then
	echo "File exists"
	rm Dirbuster_report/report.txt
else
	echo "Files does not exists" 
fi

#timeout --preserve-status 5m java -jar DirBuster-0.12/DirBuster-0.12.jar -H -t 300 -r Dirbuster_report/report.txt -u

#!/bin/bash
PATH=/bin:/sbin:/usr/bin:/usr/sbin:/usr/local/bin:/usr/local/sbin:~/bin
export PATH

#node findalldomain.js > filesforinput/domainlist.txt 

while read -r domain
	do
		    rm Dirbuster_report/report.txt
		    dirbustpre="timeout --preserve-status 5m java -jar DirBuster-0.12/DirBuster-0.12.jar -H -t 300 -r Dirbuster_report/report.txt -u " 
		    dirbustcommand=$dirbustpre$domain
		    $dirbustcommand
		    
		    echo "Dirbuster_report/report.txt" | ./parse_dirbust_report
		    
		    sh linkcheck.sh $domain
	done < filesforinput/domainlist.txt

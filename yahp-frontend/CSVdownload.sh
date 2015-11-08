#!/bin/bash
PATH=/bin:/sbin:/usr/bin:/usr/sbin:/usr/local/bin:/usr/local/sbin:~/bin
export PATH

wget http://www.malwaredomainlist.com/mdlcsv.php
mv mdlcsv.php io/export.csv

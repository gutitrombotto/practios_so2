#!/bin/bash

for i in `find /var/www/html/tp3/archivos -name *.ko` ;
do sudo rmmod $i ; 
done


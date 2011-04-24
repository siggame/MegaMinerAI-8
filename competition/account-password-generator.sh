#!/bin/bash

#This script generates acceptable passwords for the megaminer accounts.
#It requires pwgen

for i in `seq 131 155`; 
do echo mst00$i `pwgen -n -c -N 1`; 
done > mm-userpass.txt

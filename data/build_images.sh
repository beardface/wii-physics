#!/bin/bash
files=`echo *.png`
for file in $files
do
	${DEVKITPPC}/bin/raw2c $file
done 

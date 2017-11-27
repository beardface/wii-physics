#!/bin/bash
files=`echo *.ogg`
for file in $files
do
	${DEVKITPPC}/bin/raw2c $file
done 

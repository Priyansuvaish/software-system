#!/bin/bash

echo "enter the file"
read a
echo "enter the target"
read t
if ln $a $t; 
then
	echo "created successfully"
else
	echo "already exit"
fi

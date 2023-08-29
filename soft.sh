#!/bin/bash

echo "enter the file address"
read s
echo "enter the target"
read t
if ln -s $s $t;
then 
	echo "created successfully"
else
	echo "already exits"
fi

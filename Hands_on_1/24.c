/*
 Name : 24.c
Author : Priyanhu Vaish
Description : Write a program to create an orphan process.
Date: 9th Sep, 2023.
*/
#include<stdlib.h>
#include <stdio.h>
#include<unistd.h>
int main(){
	if(!fork()){
		sleep(10);
		printf("I am a orphen process");
	}
	return (0);
}

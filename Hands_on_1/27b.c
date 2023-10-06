/*
 Name : 27b.c
Author : Priyanshu  Vaish
Description : Write a program to execute ls -Rl by the following system calls
		b. execlp
Date: 9th Sep, 2023.
*/
#include <unistd.h>
#include <stdio.h>

int main() {
    printf("%d",execlp("ls", "ls", "-Rl", NULL));

}

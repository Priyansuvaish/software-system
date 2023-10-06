/*
Name : 23.c
Author : Priyanshu Vaish
Description : Write a program to print the maximum number of files can be opened within a process and size of a pipe (circular buffer).
Date: 5th Oct, 2023.
*/
#include <unistd.h>
#include <stdio.h>

int main() {
    printf("Number of file can be opened : %ld\n",  sysconf(_SC_OPEN_MAX));
    printf("size of pipe : %ld", pathconf(".", _PC_PIPE_BUF));
}

/*
Name : 1a.c
Author : Priyanshu Vaish
Description : Create the following types of a files using (i) shell command (ii) system call
		a. soft link (symlink system call)
Date: 4th Sep, 2023.
*/
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>

int main() {
    int res = symlink("./soft.c", "./softlink");

    if(res == 0)
        printf("soft link succesfully created");
    else if(res == -1)
        printf("error: %s\n", strerror(errno));
}

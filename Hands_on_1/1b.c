/*
 Name : 1b.c
Author : Priyanshu Vaish
Description : Create the following types of a files using (i) shell command (ii) system call
		b. hard link (link system call)
Date: 9th Sep, 2023.
*/
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>

int main() {
    int res = link("./hard.c", "./hardlink");

    if(res == 0)
        printf("hard link succesfully created");
    else if(res == -1)
        printf("error: %s\n", strerror(errno));
}

/*
    Name : 18a.c
Author : Priyanshu Vaish
Description : Create the following types of a files using (i) shell command (ii) system call
        	c. FIFO (mkfifo Library Function or mknod system call)
Date: 9th Sep, 2023.
*/

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>

int main() {
    int res = mkfifo("fifo1", S_IFIFO);

    if(res == 0)
        printf("succesfully created fifo file ");
    else if(res == -1)
        printf("error: %s\n", strerror(errno));
}

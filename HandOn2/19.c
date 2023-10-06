/*
Name : 19.c
Author : Priyanshu Vaish
Description : Create a FIFO file by
		a. mknod command
		b. mkfifo command
		c. use strace command to find out, which command (mknod or mkfifo) is better.
		c. mknod system call
		d. mkfifo library function
Date: 3rd Oct, 2023.
*/
mknod pipes1 p

mkfifo pipes2

strace -c mknod myfifo p 
strace -c mkfifo myfifo2

#include <stdio.h>

int main() {
    if(mknod("./fifo1", S_IFIFO | 0666, 0) == -1)
        printf("%s", strerror(errno));
   else printf("pipr is created successfully using mknod")
    if(mkfifo("./myfifo", 0666) == -1)
        printf("%s", strerror(errno));
    else printf("pipr is created successfully using mkfifo")
}


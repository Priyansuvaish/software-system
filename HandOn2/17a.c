/*
Name : 17a.c
Author : Priyanshu VAish
Description : Write a program to execute ls -l | wc.
		a. use dup
Date: 2nd Oct, 2023.
*/

#include <unistd.h>
#include <sys/stat.h>

int main() {
    int fd[2];
    pipe(fd);

    if(!fork()) {
	close(1);
        close(fd[0]);
        dup(fd[1]);
        execlp("ls", "ls", "-l", NULL);
    }
    else {
        close(fd[1]);
        close(0);
        dup(fd[0]);
        execlp("wc", "wc", NULL);
    }
}

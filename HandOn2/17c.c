/*
Name : 17c.c
Author : Priyanshu VAish
Description : Write a program to execute ls -l | wc.
		c. use fcntl
Date: 2nd Oct, 2023.
*/
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>

int main() {
    int fd[2];
    pipe(fd);

    if(!fork()) {
	close(1);
        close(fd[0]);
        fcntl(fd[1],F_DUPFD,1);
        execlp("ls", "ls", "-l", NULL);
    }
    else {
        close(fd[1]);
        close(0);
        fcntl(fd[0],F_DUPFD,0);
        execlp("wc", "wc", NULL);
    }
}

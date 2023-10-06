/*
Name : 18.c
Author : Priyanshu Vaish
Description : Write a program to find out total number of directories on the pwd.
              execute ls -l | grep ^d | wc ? Use only dup2.
Date: 2nd Oct, 2023.
*/

#include <unistd.h>
#include <sys/types.h>

int main() {
    int fd1[2];
    int fd2[2];
    pipe(fd1);
    pipe(fd2);

    if(!fork()) {
        close(fd1[0]);
        dup2(fd1[1], 1);
        close(fd2[0]);
        close(fd2[1]);
        execlp("ls", "ls", "-l", NULL);
    }
    else {
        if(!fork()) {
            close(fd1[1]);
            close(fd2[0]);
            dup2(fd1[0], 0);
            dup2(fd2[1], 1);
            execlp("grep", "grep", "^d", NULL);
        }
        else {
            close(fd1[0]);
            close(fd1[1]);
            close(fd2[1]);
            dup2(fd2[0], 0);
            execlp("wc", "wc", NULL);
        }
    }
}

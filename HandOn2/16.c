/*
Name : 16.c
Author : Priyanshu vaish
Description : Write a program to send and receive data from parent to child vice versa.
              Use two way communication.
Date: 1st Oct, 2023.
*/

#include <unistd.h>
#include <stdio.h>
#include <sys/stat.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>

int main() {
    int fd1[2], fd2[2];
    pipe(fd1);
    pipe(fd2);

    if(!fork()) {
        close(fd1[0]);
        char buff[30];
	printf("enter the message to parrent\n");
	scanf("%s",&buff);
        write(fd1[1], &buff, sizeof(buff));
        close(fd2[1]);
        read(fd2[0], &buff, 30);
        printf("message from parent: %s\n", buff);
    }
    else {
        close(fd1[1]);
        char buff[30];

        read(fd1[0], &buff, 30);
        printf("message from child : %s\n", buff);

        close(fd2[0]);
	printf("enter the message to child\n");
	scanf("%s",&buff);
        write(fd2[1], &buff, sizeof(buff));
    }
}

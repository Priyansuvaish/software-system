/*
 Name : 11.c
Author : Priyanshu Vaish
Description : Write a program to open a file, duplicate the file descriptor and append the file with both the
descriptors and check whether the file is updated properly or not.
a. use dup
b. use dup2
c. use fcntl
Date: 9th Sep, 2023.
*/
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>

int main() {
    int fd = open("./11.c", O_RDWR | O_APPEND);

    if(fd == -1) {
        printf("error: %s\n", strerror(errno));
        return 0;
    }

    int dfd = dup(fd); 
    int fd2 = dup2(fd, 99);

    if(dfd == -1) {
        printf("error: %s\n", strerror(errno));
        return 0;
    }

    if(fd2 == -1) {
        printf("error: %s\n", strerror(errno));
        return 0;
    }

    if(write(dfd, "duplicate using dup",20) == -1) {
        printf("error: %s\n", strerror(errno));
        return 0;
    }

    if(write(fd2, "duplicate using dup2", 20) == -1) {
        printf("error: %s\n", strerror(errno));
        return 0;
    }

    int ffd = fcntl(fd, F_DUPFD, 3);

    if(ffd == -1) {
        printf("error: %s\n", strerror(errno));
        return 0;
    }

    if(write(ffd, "duplicate using fcntl", 20) == -1) {
        printf("error: %s\n", strerror(errno));
        return 0;
    }

    close(fd);
    close(dfd);
    close(fd2);
    close(ffd);

}

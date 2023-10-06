/*
 Name : 17.c
Author : Priyanshu Vaish
Description : Write a program to open a file, store a ticket number and exit.
Date: 9th Sep, 2023.
*/
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
struct d{
	int tnum;
};

int main() {
    int fd = open("./db", O_CREAT | O_WRONLY);

    if(fd == -1) {
        printf("error: %s\n", strerror(errno));
        return 0;
    }

    struct d t;
    t.tnum = 58;

    struct flock f;
    f.l_type = F_WRLCK;
    f.l_whence = SEEK_SET;
    f.l_start = 0;
    f.l_len = sizeof(t);
    f.l_pid = getpid();

    
    if(fcntl(fd, F_SETLKW, &f) == -1) {
        printf("error: %s\n", strerror(errno));
        return 0;
    }

    if(write(fd, &t, sizeof(t)) == -1) {
        printf("error: %s\n", strerror(errno));
        return 0;
    }
     getchar();
    f.l_type = F_UNLCK;

    if(fcntl(fd, F_SETLK, &f) == -1) {
        printf("error: %s\n", strerror(errno));
        return 0;
    }

    close(fd);
}

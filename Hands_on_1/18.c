/*
 Name : 18.c
Author : Priyanshu Vaish
Description : Create three records in a file
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
    char a[10] = "data a \n";
    char b[10] = "data b \n";
    char c[10] = "data c \n";

    int fd = open("temp.txt", O_CREAT | O_WRONLY);

    if(fd == -1) {
        printf("file not exi");
       return(0);
    }

    struct flock r1;
    struct flock r2;
    struct flock r3;

    r1.l_type = F_WRLCK;
    r1.l_whence = SEEK_SET;
    r1.l_start = 0;
    r1.l_len = 10;
    r1.l_pid = getpid();
    fcntl(fd, F_SETLKW, &r1);

    r2.l_type = F_WRLCK;
    r2.l_whence = SEEK_SET;
    r2.l_start = 11;
    r2.l_len = 10;
    r2.l_pid = getpid();
    fcntl(fd, F_SETLKW, &r2);

    r3.l_type = F_WRLCK;
    r3.l_whence = SEEK_SET;
    r3.l_start = 21;
    r3.l_len = 10;
    r3.l_pid = getpid();
    fcntl(fd, F_SETLKW, &r3);

    write(fd, &a, 10);
    write(fd, &b, 10);
    write(fd, &c, 10);

    r1.l_type = F_UNLCK;
    fcntl(fd, F_SETLK, &r1);

    r2.l_type = F_UNLCK;
    fcntl(fd, F_SETLK, &r2);
    
    r3.l_type = F_UNLCK;
    fcntl(fd, F_SETLK, &r3);

    close(fd);
}

/*
 Name : 17r.c
Author : Priyanshu Vaish
Description : Write a separate program, to
open the file, implement write lock, read the ticket number, increment the number and print
the new ticket number then close the file.
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
    int fd = open("./db", O_RDWR);

    if(fd == -1) {
        printf("error: %s\n", strerror(errno));
        return 0;
    }

    struct d t;
    struct flock f;

    f.l_type = F_RDLCK;
    f.l_whence = SEEK_SET;
    f.l_start = 0;
    f.l_len = sizeof(t);
    f.l_pid = getpid();

    if(fcntl(fd, F_SETLKW, &f) == -1) {
        printf("error: %s\n", strerror(errno));
        return 0;
    }
    
    if(read(fd, &t, sizeof(t)) == -1) {
        printf("error: %s\n", strerror(errno));
        return 0;
    }

    f.l_type = F_UNLCK;

    if(fcntl(fd, F_SETLKW, &f) == -1) {
        printf("error: %s\n", strerror(errno));
        return 0;
    }

    printf("current ticket num : %d", t.tnum);
    t.tnum++;
    lseek(fd, 0, SEEK_SET);
    f.l_type = F_WRLCK;

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

    if(fcntl(fd, F_SETLKW, &f) == -1) {
        printf("error: %s\n", strerror(errno));
        return 0;
    }  

    close(fd);
}

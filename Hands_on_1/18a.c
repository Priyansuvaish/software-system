/*
 Name : 18a.c
Author : Priyanshu Vaish
Description : Write a C, Ansi-style program to perform Record locking.
                       a. Implement write lock
Date: 9th Sep, 2023.
*/
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>

int main() {
    char a[10] = "data new \n";
    int fd = open("temp.txt", O_WRONLY);

    if(fd == -1) {
        printf("file not exit");
       return(0);
    }

    struct flock r1;

    r1.l_type = F_WRLCK;
    r1.l_whence = SEEK_SET;
    r1.l_start = 21;
    r1.l_len = 10;
    r1.l_pid = getpid();
    fcntl(fd, F_SETLKW, &r1);
	lseek(fd, 20, SEEK_SET);
    write(fd, &a, 10);
getchar();
    r1.l_type = F_UNLCK;
    fcntl(fd, F_SETLK, &r1);

    close(fd);
}

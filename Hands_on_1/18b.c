/*
 Name : 18b.c
Author : Priyanshu Vaish
Description : Write a C, Ansi-style program to perform Record locking.
                       b. Implement read lock
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
	char a[10],b[10];
    int fd = open("temp.txt", O_RDONLY);

    if(fd == -1) {
        printf("file not exi");
       return(0);
    }

    struct flock r1;
    struct flock r2;

    r1.l_type = F_RDLCK;
    r1.l_whence = SEEK_SET;
    r1.l_start = 0;
    r1.l_len = 10;
    r1.l_pid = getpid();
    fcntl(fd, F_SETLKW, &r1);
	
    r2.l_type = F_RDLCK;
    r2.l_whence = SEEK_SET;
    r2.l_start = 11;
    r2.l_len = 10;
    r2.l_pid = getpid();
    fcntl(fd, F_SETLKW, &r2);
// 	getchar();
	read(fd, &a, 10);
	printf("%s\n",a);
    read(fd, &b, 10);
    printf("%s\n",b);
    r1.l_type = F_UNLCK;
    fcntl(fd, F_SETLK, &r1);

    r2.l_type = F_UNLCK;
    fcntl(fd, F_SETLK, &r2);
    
    close(fd);
}

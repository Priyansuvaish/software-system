/*
Name : 20r.c
Author : Priyanhu vaish
Description : Write two programs so that both can communicate by FIFO -Use one way communication.
Date: 4th Oct, 2023.
*/
#include <sys/time.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

int main() {
    int fd = open("./fifo1", O_RDONLY);
    char buff[20];

    if(fd == -1) {
        printf("%s", strerror(errno));
        return 0;
    }
    fd_set rfds;
    struct timeval t1;
    int r;

    FD_ZERO(&rfds);
    FD_SET(fd, &rfds);
    t1.tv_sec = 10;
    t1.tv_usec = 0;

    r = select(fd+1, &rfds, NULL, NULL, &t1);
    if(r==0)printf(" data not entered");
    else{
    read(fd, buff, sizeof(buff));
    printf("%s", buff);
 }
    close(fd);
}  

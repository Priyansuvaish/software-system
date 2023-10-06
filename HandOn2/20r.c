/*
Name : 20r.c
Author : Priyanhu vaish
Description : Write two programs so that both can communicate by FIFO -Use one way communication.
Date: 4th Oct, 2023.
*/

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

    read(fd, buff, sizeof(buff));
    printf("%s", buff);
    close(fd);
}  

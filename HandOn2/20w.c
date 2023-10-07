/*
Name : 20w.c
Author : Priyanshu Vaish
Description : Write two programs so that both can communicate by FIFO -Use one way communication.
Date: 4th Oct, 2023.
*/
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

int main() {
    if(mknod("./fifo1", S_IFIFO | 0666, 0) == -1)
        printf("%s", strerror(errno));

    int fd = open("./fifo1", O_WRONLY);
    char buff[20];

    if(fd == -1) {
        printf("%s", strerror(errno));
        return 0;
    }

    printf("Enter text for pipe :");
    scanf("%[^\n]", buff);
    write(fd, buff, sizeof(buff));
    close(fd);
}

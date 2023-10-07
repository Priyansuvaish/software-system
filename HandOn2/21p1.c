/*
Name : 21p1.c
Author : Priyanshu Vaish
Description : Write two programs so that both can communicate by FIFO -Use two way communications.
Date: 4th Oct, 2023
*/
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

int main() {
    int fd1 = open("./fifo1", O_WRONLY);
    int fd2 = open("./fifo2", O_RDONLY);    
    char buff[20];
    if(fd1==-1)printf("file not exit");
    if(fd2==-1)printf("file not exit");
    printf("Enter text for pipe :");
    scanf("%[^\n]", buff);
    write(fd1, buff, sizeof(buff));
    read(fd2, buff, sizeof(buff));

    printf("%s", buff);
}

/*
 Name : 5.c
Author : Priyanshu Vaish
Description : Write a program to create five new files with infinite loop.
Date: 9th Sep, 2023.
*/
#include <fcntl.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
int main()
{
    int c = 5;
    char path[10];
    int fd = -1;

    for (;1;)
    {
        if (c > 0)
        {
            sprintf(path, "%d.txt", c);
            fd = creat(path, O_RDONLY);
            
            if(fd == -1)
                printf("error: %s\n", strerror(errno));
            else {
                printf("file created \n file descriptor value %d \n", fd);
                c--;
            }
        }else return 0;
  }
}

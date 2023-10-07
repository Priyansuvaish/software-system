/*
Name : 33c.c
Author : Priyanshu Vaish
Description : Write a program to communicate between two machines using socket.
*/
#include <fcntl.h>
#include <sys/socket.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <arpa/inet.h>

int main() {
    struct sockaddr_in ser;
    int sd = socket(AF_UNIX, SOCK_STREAM, 0);
    char buff[80];

    ser.sin_family = AF_UNIX;
    ser.sin_addr.s_addr = INADDR_ANY;
    ser.sin_port = htons(9999);

    if(connect(sd, (void *)(&ser), sizeof(ser)) == -1) {
        printf("%s", strerror(errno));
        return 0;
    }

    write(sd, "Hello server\n", 14);
    read(sd, buff, sizeof(buff));
    printf("Message from Server : %s", buff);
}

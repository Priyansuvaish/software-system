/*
Name : 33s.c
Author : Priyanshu Vaish
Description : Write a program to communicate between two machines using socket.
*/
#include <fcntl.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <stdio.h>
#include <arpa/inet.h>

int main() {
    struct sockaddr_in ser, cli;
    int sd = socket(AF_UNIX, SOCK_STREAM, 0);
    int nsd,sz;
    char buff[80];

    ser.sin_family = AF_UNIX;
    ser.sin_addr.s_addr = INADDR_ANY;
    ser.sin_port = htons(9999);

    bind(sd, (void *)(&ser), sizeof(ser));
    listen(sd, 5);
    sz=sizeof(cli);
    nsd = accept(sd, (void *)(&cli), &sz);

    read(nsd, buff, sizeof(buff));
    printf("message from Client : %s", buff);
    write(nsd, "msg received\n", 13);

    close(nsd);
}

/*
 Name : 30.c
Author : Priyanshu Vaish
Description : Write a program to run a script at a specific time using a Daemon process.
Date: 9th Sep, 2023.
*/

#include <unistd.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <stdio.h>

int main() {
    if(!fork()) {
        setsid();
        //chdir("/");
        umask(0);

        while(1) {
            sleep(3);
            printf("Daemon process PID is %d\n", getpid());
        }
    }
    return(0);
}

/*
 Name : 29.c
Author : Priyanshu Vaish
Description : Write a program to remove the message queue
*/
#include <sys/msg.h>
#include <errno.h>
#include <string.h>
#include <stdio.h>

int main() {
    key_t key = ftok(".", 7);
    int msgq_id = msgget(key, 0);

    if(msgctl(msgq_id, IPC_RMID, 0) == -1) {
        printf("%s", strerror(errno));
        return 0;
    }
}

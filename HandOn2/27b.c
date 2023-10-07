/*
Name : 15.c
Author : Priyanshu Vaish
Description : Write a program to receive messages from the message queue.
        a. with 0 as a flag
*/
#include <sys/msg.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>

int main() {
    key_t key = ftok(".", 7);
    int msgq_id = msgget(key, 0);
    struct msgbuf {
        long int mtype;
        char mtext[80];
    }msg1;
    printf("enter the message type: ");
    scanf("%ld",&msg1.mtype);
    if(msgrcv(msgq_id, &msg1, sizeof(msg1.mtext), msg1.mtype, IPC_NOWAIT) == -1) {
        printf("%s", strerror(errno));
        return 0;
    }

    printf("\nThe message type: %ld", msg1.mtype);
    printf("\nmsg: %s", msg1.mtext);
}

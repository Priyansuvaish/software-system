/*
Name : 23.c
Author : Priyanshu Vaish
Description : Write a program to send messages to the message queue. Check $ipcs -q
*/

#include <sys/msg.h>
#include <errno.h>
#include <string.h>
#include <stdio.h>

int main() {
    key_t key = ftok(".", 7);
    int msgq_id = msgget(key, 0); 

    struct msg {
        long int mtype;
        char mtext[80];
    }msg1;
    printf("enter the message type");
    scanf("%ld",msg1.mtype);
    
    printf("enter the message:");
    scanf("%s",msg1.mtext);

    int size = strlen(msg1.mtext);
    if(msgq_id == -1) {
        printf("%s", strerror(errno));
        return 0;
    }

    if(msgsnd(msgq_id, &msg1, size+1, 0) == -1) {
        printf("%s", strerror(errno));
        return 0;
    }
}

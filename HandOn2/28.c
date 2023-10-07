/*
Name : 28.c
Author : Priyanshu Vaish
Description :Write a program to change the exiting message queue permission. (use msqid_ds structure)
*/
#include <sys/msg.h>
#include <errno.h>
#include <string.h>
#include <stdio.h>

int main() {
    key_t key = ftok(".", 7);
    int msgq_id = msgget(key, 0);
    struct msqid_ds p;

    p.msg_perm.uid = 70;
    p.msg_perm.gid = 50;
    p.msg_perm.mode = 0700;
    
    if(msgctl(msgq_id, IPC_SET, &p) == -1) {
        printf("%s", strerror(errno));
        return 0;
    }
}

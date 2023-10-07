/*
Name : 25.c
Author : Priyanshu Vaish
Description : Write a program to print a message queue's  (use msqid_ds and ipc_perm structures)
        a. access permission
        b. uid, gid
        c. time of last message sent and received   
        d. time of last change in the message queue
        e. size of the queue
        f. number of messages in the queue 
        g. maximum number of bytes allowed 
        h. pid of the msgsnd and msgrcv
*/
#include <time.h>
#include <sys/msg.h>
#include <stdio.h>



int main() {
    key_t key = ftok(".", 7);
    int msgq_id = msgget(key, 0);

    struct ipc_perm msg;
    struct msqid_ds mq;
    struct msginfo info;

    if(msgq_id == -1) {
        printf("error");
        return 0;
    }

    msgctl(msgq_id, IPC_STAT, &mq);
    printf("Acess Permissions: %03o\n", mq.msg_perm.mode & 0777);
    printf("UID of owner: %d\n", msg.uid);
    printf("GID of owner: %d\n", msg.gid);
    printf("Time of last msg send at: %s and recive at : %s ", ctime(&mq.msg_stime), ctime(&mq.msg_rtime));
    printf("Time of last change in the message queue : %s", ctime(&mq.msg_ctime));
    printf("size of the queue %lu\n",mq.msg_cbytes);
    printf("Current number of message in queue: %lu\n", mq.msg_qnum);
    printf("Maximum number of bytes allowed : %lu\n", mq.msg_qbytes);
    printf("PID of last msg send: %d and recevied: %d", mq.msg_lspid, mq.msg_lrpid);
}

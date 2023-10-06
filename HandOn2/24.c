/*
 Name : 24.c
Author : Priyanshu Vaish
Description : Write a program to create a message queue and print the key and message queue id.
Date: 5th Oct, 2023.
*/

#include <sys/msg.h>
#include <stdio.h>


int main() {
    key_t key = ftok(".", 7);
    int msgq_id;

    msgq_id = msgget(key, IPC_CREAT | IPC_EXCL | 0766);
    printf("key : %d", key);
    printf("\nkey value in hex 0x%0x", key);
    printf("\nmessage queue id: %d", msgq_id);
}

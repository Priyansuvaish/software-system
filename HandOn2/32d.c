/*
Name : 32d.c
Author : Priyanshu Vaish
Description :Write a program to implement semaphore to protect any critical section
        d. remove the created semaphore
*/
#include <sys/sem.h>
#include <stdio.h>

int main() {
    key_t key1 = ftok("binarysema1", 0);
    key_t key2 = ftok("countingsem1", 74);

    int sem_id1 = semget(key1, 1, 0);
    int sem_id2 = semget(key2, 2, 0);

    semctl(sem_id1, IPC_RMID, 0);
    semctl(sem_id2, IPC_RMID, 0);
}

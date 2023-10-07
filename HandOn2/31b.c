/*
Name : 31b.c
Author : Priyanshu Vaish
Description : Write a program to create a semaphore and initialize value to the semaphore.
         b. create a counting semaphore
*/
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>

union semun {
  int val;      // value for SETVAL 
  struct semid_ds *buf;  // buffer for IPC_STAT
  unsigned short int *array;  // array for GETALL
 };

int main() {
    key_t key = ftok("sm", 10);
    int sem_id = semget(key, 2, IPC_CREAT|0644);
    union semun arg;
    arg.val = 2;

    semctl(sem_id, 1, SETVAL, arg);
}

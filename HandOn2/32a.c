/*
Name : 32a.c
Author : Priyanshu Vaish
Description : Write a program to create a semaphore and initialize value to the semaphore.
         a. rewrite the ticket number creation program using semaphore
*/
#include <sys/sem.h>
#include <errno.h>
#include <string.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

union semun {
  int val;      // value for SETVAL 
  struct semid_ds *buf;  // buffer for IPC_STAT
  unsigned short int *array;  // array for GETALL
};

struct ticket_db{
    int tnum;
};

int main() {
    key_t key = ftok("binarysema1", 7);
    int sem_id = semget(key, 1, IPC_CREAT);
    union semun arg;
    int fd = open("ticket.txt", O_CREAT | O_RDWR, 0766);
    struct ticket_db tk;
    tk.tnum = 10;

    if(fd == -1) {
        printf("%s", strerror(errno));
        return 0;
    }

    if(sem_id == -1) {
        printf("%s", strerror(errno));
        return 0;
    }

    arg.val = 1;

    if(semctl(sem_id, 0, SETVAL, arg) == -1) {
        printf("%s", strerror(errno));
        return 0;
    }

    struct sembuf buf = {0, -1, 0};
    semop(sem_id, &buf, 1);
    
    printf("Inside critical section\n");
    printf("Enter to increment ticket number and unlock semaphore\n");
    getchar();

    tk.tnum++;
    lseek(fd, 0, SEEK_SET);
    write(fd, &tk, sizeof(tk));
    close(fd);

    buf.sem_op = 1;
    semop(sem_id, &buf, 1);
    printf("Outside critical section\n");

}

/*Name : 30c.c
Author : Priyanshu Vaish
Description :Write a program to create a shared memory.
         c. detach the shared memory
*/
#include <sys/shm.h>
#include <errno.h>
#include <string.h>
#include <stdio.h>

int main() {
    char *add;
    key_t key = ftok(".", 'a');
    int shm_id = shmget(key, 1024, 0);

    if(shm_id == -1) {
        printf("%s", strerror(errno));
        return 0;
    }
    add = shmat(shm_id, 0, 0);
    
    if(shmdt(add) == -1) {
        printf("%s", strerror(errno));
        return 0;
    }
}   

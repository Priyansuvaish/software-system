/*Name : 30b.c
Author : Priyanshu Vaish
Description :Write a program to create a shared memory.
        b.  attach with O_RDONLY and check whether you are able to overwrite.
*/
#include <sys/shm.h>
#include <errno.h>
#include <string.h>
#include <stdio.h>

int main() {
    char *data;
    key_t key = ftok(".", 'a');
    int shm_id = shmget(key, 1024, 0);

    if(shm_id == -1) {
        printf("%s", strerror(errno));
        return 0;
    }

    data = shmat(shm_id, 0, SHM_RDONLY);
    
    printf("Data to add in shared memory : ");
    scanf("%s", data);
}   

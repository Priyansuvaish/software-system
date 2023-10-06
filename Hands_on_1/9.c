/*
 Name : 9.c
Author : Priyanshu Vaish
Description : Write a program to print the following information about a given file.
a. inode
b. number of hard links
c. uid
d. gid
e. size
f. block size
g. number of blocks
h. time of last access
i. time of last modification
j. time of last change
Date: 9th Sep, 2023.
*/
#include <sys/stat.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>


int main(int argc, char *argv[])
{
    struct stat info;

    if (argc != 2)
    {
        printf("Usage: %s <pathname>\n", argv[0]);
    }

    if (lstat(argv[1], &info) == -1)
    {
        perror("lstat");
    }

    printf("I-node:                        %ld\n", (long)info.st_ino);
    printf("Number of Hard link:           %ld\n", (long)info.st_nlink);
    printf("User ID:                       %d\n", (int)info.st_uid);
    printf("Group ID:                      %d\n", (int)info.st_gid);
    printf("Size:                          %lld bytes\n",(long long)info.st_size);
    printf("block size:   		   %ld bytes\n",(long)info.st_blksize);
    printf("Blocks allocated:              %lld\n",(long long)info.st_blocks);
    printf("Time of the last change:       %s", ctime(&info.st_ctime));
    printf("Last file access time:         %s", ctime(&info.st_atime));
    printf("Last time file modification:   %s", ctime(&info.st_mtime));
}

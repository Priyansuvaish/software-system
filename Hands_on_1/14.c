
/*
 Name : 14.c
Author : Priyanshu Vaish
Description : Write a program to find the type of a file.
a. Input should be taken from command line.
b. program should be able to identify any type of a file.
Date: 9th Sep, 2023.
*/
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
    struct stat info;
    
    if(argc != 2){
        printf("give file path : ");
        return 0;
    }

    if(stat(argv[1], &info) == -1) {
        printf("file not exit");
        return 0;
    }
    else{
        printf("The file is of type:  ");

   if(info.st_mode & S_IFMT == S_IFBLK){  
	printf("block device\n");            
	}
   else if(info.st_mode & S_IFMT == S_IFCHR){ 
	printf("character device\n");        
	}
   else if(info.st_mode & S_IFMT == S_IFDIR){
	printf("directory\n");               
	}
   else if(info.st_mode & S_IFMT == S_IFIFO){ 
	printf("FIFO/pipe\n");               
	}
   else if(info.st_mode & S_IFMT ==  S_IFLNK){ 
	printf("symlink\n");                 
	}
   else if(info.st_mode & S_IFMT ==  S_IFREG){ 
	printf("regular file\n");            
	}
   else if(info.st_mode & S_IFMT == S_IFSOCK){ 
	printf("socket\n");                  
	}
   else printf("unknown?\n");
    }
}

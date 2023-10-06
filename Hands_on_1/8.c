/*
 Name : 8.c
Author : Priyanshu Vaish
Description : Write a program to open a file in read only mode, read line by line and display each line as it is read.
Close the file when end of file is reached.
Date: 9th Sep, 2023.
*/
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
    
    int cn = 0;
    int buffer = 10;
    char * buff = (char *) malloc (buffer*sizeof(char));
    char c;
    int fd_open = open("soft.c", O_RDONLY);
    if(fd_open == -1 ) 
	printf("file not exit");
    while(read(fd_open, &c, 1)) {
        if(c == '\n') {
		write(STDOUT_FILENO, buff,cn);
		cn = 0;
	}
	else{
		if (cn == buffer){
			buffer = 2 * buffer;
			char * buff = realloc(buff,buffer);
		}
		buff[cn++] = c;
	}
    }
	write(STDOUT_FILENO, buff,cn);
	free(buff);
	close(fd_open);
}


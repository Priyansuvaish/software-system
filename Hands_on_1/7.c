/*
 Name : 7.c
Author : Priyanshu Vaish
Description : Write a program to copy file1 into file2 ($cp file1 file2).
Date: 9th Sep, 2023.
*/
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
int main(){
	int fd1 = open("5.c",O_RDONLY);
	int fd2 = open("temp.c", O_WRONLY|O_CREAT|S_IRWXU);
	while(1){
		char c;
		int r = read(fd1,&c,1);
		printf("%d",r);
		if(r!= 0)write(fd2,&c,1);
		else{
			printf("copy successfully");
			return 0;
		}
	}
}

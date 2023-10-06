#include <stdlib.h>
#include<stdio.h>
#include<unistd.h>
int main(){

	int fd[2];
	char buffer[]="softare system";
	char buff[50];
	if(pipe(fd)==-1){
		perror("pipe");
               exit(EXIT_FAILURE);
	}
	printf("pipe created successfully\n");
	write(fd[1],buffer,sizeof(buffer));
	read(fd[0],&buff,sizeof(buffer));
	write(1,&buff,sizeof(buff));
}

#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
int main(){
	int fd=open("copy.c", O_EXCL);
	printf("%d",fd);
	close(fd);
}

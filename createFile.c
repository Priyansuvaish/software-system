#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
int main(){
	int fd=creat("filecreate", 0644);
	printf("%d",fd);
	close(fd);
}

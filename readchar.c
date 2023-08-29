#include <sys/types.h>
#include <sys/stgt.h>
#include <fcnt1.h>
#include <stdio.h>
#include <unistd.h>

int main(int arhc, char* argv[]){
	if(argv!=3){
		printf("you are useless");
		return 0;
	}
	int fd= open(argv[1],O_RDONLY);
	int fd_write=open(argv[2],O_WRONLY|O_CREAT);
	if (fd==-1||fd_write==-1)
		printf("useless");
	while(1){
		char buf;
		int char_read=read(fd,&buf,1);
		if(char_read==0)
			break;
		int char_write=write(fd_write,buff,1);
	}
	int fd_close=close(fd);
	int fd_write_close=close(fd_write);
	if (fd_close==-1||fd_write_close==-1)
		printf("totally useless");
	return 0;

}

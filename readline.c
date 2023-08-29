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
    while(read(fd_open, &c, 1)) {
        if(c == '\n') {
		printf("%s \n", buff);
		cn = 0;
	}
	else{
		cn++;
		if (cn == buffer){
			buffer = 2 * buffer;
			char * buff = realloc(buff,buffer);
		}
		buff[cn] = c;
	}
    }
	printf("%s \n", buff);
	free(buff);
	close(fd_open);
}


#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>

int main() {
    // soft link
    const char *linkpath = "./hard.c";
    const char *target = "./hard_link";

    int res = link(linkpath, target);

    if(res == 0)
        printf("hard link succesfully created\n %s -> %s \n", linkpath, target);
    else if(res == -1)
        printf("error: %s\n", strerror(errno));
}

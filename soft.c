#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>

int main() {
    // soft link
    const char *linkpath = "./soft.c";
    const char *target = "./soft_link";

    int res = symlink(linkpath, target);

    if(res == 0)
        printf("soft link succesfully created\n %s -> %s \n", linkpath, target);
    else if(res == -1)
        printf("error: %s\n", strerror(errno));
}

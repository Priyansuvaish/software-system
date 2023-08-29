#include <unistd.h>
#include <stdio.h>

int main() {
    
    while(*__environ){
        printf("%s\n", *__environ);
        *__environ++;
    }
}

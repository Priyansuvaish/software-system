/*
 Name : 15.c
Author : Priyanshu Vaish
Description : Write a program to display the environmental variable of the user (use environ).
Date: 9th Sep, 2023.
*/
#include <unistd.h>
#include <stdio.h>

int main() {
    
    while(*__environ){
        printf("%s\n", *__environ);
        *__environ++;
    }
}

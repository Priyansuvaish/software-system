#ifndef FUNCTIONS
#define FUNCTIONS
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <errno.h>

#include "./record.h"

bool login_handler(int type, int connFD,struct professor *proff,struct student *sd);
int add_account(int connFD, int type);

bool login_handler(int type, int connFD,struct professor *proff,struct student *sd)
{
    ssize_t readBytes, writeBytes;
    char readBuffer[1000], writeBuffer[1000];
    char tempBuffer[1000];
    int i;
    struct professor p={0};
    struct student s={0};

    bzero(readBuffer, sizeof(readBuffer));
    bzero(writeBuffer, sizeof(writeBuffer));

    strcpy(writeBuffer, "Enter the credential\n");


    strcat(writeBuffer, "enter the username\n");

    writeBytes = write(connFD, writeBuffer, strlen(writeBuffer));
    if (writeBytes == -1)
    {
        perror("Error writing WELCOME & LOGIN_ID message to the client!");
        return false;
    }

    readBytes = read(connFD, readBuffer, sizeof(readBuffer));
    if (readBytes == -1)
    {
        perror("Error reading login ID from client!");
        return false;
    }

    bool userFound = false;

    if (type ==1)
    {
        if (strcmp(readBuffer, "root") == 0)
            userFound = true;
    }
    if(type == 2)
    {
        i = 0;
        off_t offset ;
        int customerFileFD = open("./professor.txt",O_RDONLY);
        if (customerFileFD == -1)
        {
            perror("Error opening customer file in read mode!");
            return false;
        }

         while(read(customerFileFD,&p,sizeof(struct professor)))
        {
          if(strcmp(p.login,readBuffer)!=0)
          {
            i=i+1;
           offset= lseek(customerFileFD, i*sizeof(struct professor),SEEK_SET);
          }
	  else {userFound=true;break;}
	}
          close(customerFileFD);
	 if(userFound == false)
          writeBytes = write(connFD, "LOGIN_ID_DOESNT_EXIT", 19);
    }
    if (type ==3)
    {
        i = 0;

        int studentFileFD = open("./student.txt",O_RDONLY);
        if (studentFileFD == -1)
        {
            perror("Error opening customer file in read mode!");
            return false;
        }
        while(read(studentFileFD,&s,sizeof(struct student)))
        {
          if(strcmp(s.login,readBuffer)!=0)
          {    
            i=i+1;
           lseek(studentFileFD,i*sizeof(struct professor),SEEK_SET);
          }
          else{
		 userFound=true;break;
	      }
        }
            close(studentFileFD);
    }
    if (userFound)
    {
        bzero(writeBuffer, sizeof(writeBuffer));
        writeBytes = write(connFD, "enter the password\n", 20);
        if (writeBytes == -1)
        {
            perror("Error writing PASSWORD message to client!");
            return false;
        }

        bzero(readBuffer, sizeof(readBuffer));
        readBytes = read(connFD, readBuffer, sizeof(readBuffer));
        if (readBytes == 1)
        {
            perror("Error reading password from the client!");
            return false;
       }
        if (type == 1)
        {
            if (strcmp(readBuffer, "root") == 0)
            {
                 return true;
            }
        }
        if(type == 2)
        { 
            if (strcmp(readBuffer, p.password) == 0)
            {
                *proff =p;
                return true;
            }
        }
        if (type == 3)
        {
            if (strcmp(readBuffer, s.password) == 0)
            {
                *sd=s;
                return true;
            }
        }
        else{
        bzero(writeBuffer, sizeof(writeBuffer));
        writeBytes = write(connFD, "INVALID_PASSWORD", 16);
        }
    }
    else
    {
        bzero(writeBuffer, sizeof(writeBuffer));
        writeBytes = write(connFD, "INVALID_LOGIN", 13);
    }

    return false;
}
int add_account(int connFD, int type)
{
    ssize_t readBytes, writeBytes;
    char readBuffer[1000], writeBuffer[1000];

    struct professor  pn={0},pp={0};
    struct student   sn={0},ss={0};
    if(type == 1)
    {  
       int accountFileDescriptor = open("professor.txt", O_RDONLY);
    if (accountFileDescriptor == -1 && errno == ENOENT)
    {
        // Account file was never created
        pn.id = 0;
    }
    else if (accountFileDescriptor == -1)
    {
        perror("Error while opening account file");
        return false;
    }
    else
    {
        int offset = lseek(accountFileDescriptor, -sizeof(struct professor), SEEK_END);
        if (offset == -1)
        {
            perror("Error seeking to last Account record!");
            return false;
        }

        struct flock lock = {F_RDLCK, SEEK_SET, offset, sizeof(struct professor), getpid()};
        int lockingStatus = fcntl(accountFileDescriptor, F_SETLKW, &lock);
        if (lockingStatus == -1)
        {
            perror("Error obtaining read lock on Account record!");
            return false;
        }

        readBytes = read(accountFileDescriptor, &pp, sizeof(struct professor));
        if (readBytes == -1)
        {
            perror("Error while reading Account record from file!");
            return false;
        }

        lock.l_type = F_UNLCK;
        fcntl(accountFileDescriptor, F_SETLK, &lock);
        lseek(accountFileDescriptor, 0, SEEK_SET);
        close(accountFileDescriptor);

        pn.id = pp.id + 1;
    }
       
       writeBytes = write(connFD, "Enter the name\n", 16);
       if (writeBytes == -1)
       {
         perror("Error writing NAME to client!");
         return false;
       }
       bzero(readBuffer, sizeof(readBuffer));
       readBytes = read(connFD, readBuffer, sizeof(readBuffer));
       if (readBytes == -1)
       {
        perror("Error reading customer name response from client!");
        return false;
       }

       strcpy(pn.name, readBuffer);

       bzero(writeBuffer, sizeof(writeBuffer));
       strcpy(writeBuffer, "Enter the age");
       writeBytes = write(connFD, writeBuffer, strlen(writeBuffer));
       if (writeBytes == -1)
       {
        perror("Error writing the AGE message to client!");
        return false;
       }

       bzero(readBuffer, sizeof(readBuffer));
       readBytes = read(connFD, readBuffer, sizeof(readBuffer));
       if (readBytes == -1)
       {
        perror("Error reading the age response from client!");
        return false;
       }

       int Age = atoi(readBuffer);
       if (Age == 0)
       {
        bzero(writeBuffer, sizeof(writeBuffer));
        strcpy(writeBuffer, "ERRON_INPUT_FOR_NUMBER");
        writeBytes = write(connFD, writeBuffer, strlen(writeBuffer));
        if (writeBytes == -1)
         {
            perror("Error while writing ERRON_INPUT_FOR_NUMBER message to client!");
            return false;
         }
        readBytes = read(connFD, readBuffer, sizeof(readBuffer)); // Dummy read
        return false;
        }
        pn.age = Age;

        writeBytes = write(connFD, "Enter the username\n", 20);
        if (writeBytes == -1)
        {
         perror("Error writing USERNAME to client!");
         return false;
        }
        bzero(readBuffer, sizeof(readBuffer));
        readBytes = read(connFD, readBuffer, sizeof(readBuffer));
        if (readBytes == -1)
        {
         perror("Error reading username response from client!");
         return false;
        }

        strcpy(pn.login, readBuffer);

        writeBytes = write(connFD, "Enter the password\n", 20);
        if (writeBytes == -1)
        {
         perror("Error writing password to client!");
         return false;
        }
        bzero(readBuffer, sizeof(readBuffer));
        readBytes = read(connFD, readBuffer, sizeof(readBuffer));
        if (readBytes == -1)
        {
         perror("Error reading password response from client!");
         return false;
        }

        strcpy(pn.password, readBuffer);

        int professorFileDescriptor = open("professor.txt", O_CREAT | O_APPEND | O_WRONLY, S_IRWXU);
        if (professorFileDescriptor == -1)
        {
         perror("Error while creating / opening customer file!");
         return false;
        }
        writeBytes = write(professorFileDescriptor, &pn, sizeof(pn));
        if (writeBytes == -1)
        {
         perror("Error while writing Customer record to file!");
         return false;
        }

       close(professorFileDescriptor);
    }
    if(type == 2)
    {

       int accountFileDescriptor = open("student.txt", O_RDONLY);
    if (accountFileDescriptor == -1 && errno == ENOENT)
    {
        // Account file was never created
        sn.id = 0;
    }
    else if (accountFileDescriptor == -1)
    {
        perror("Error while opening account file");
        return false;
    }
    else
    {
        int offset = lseek(accountFileDescriptor, -sizeof(struct student), SEEK_END);
        if (offset == -1)
        {
            perror("Error seeking to last Account record!");
            return false;
        }

        struct flock lock = {F_RDLCK, SEEK_SET, offset, sizeof(struct student), getpid()};
        int lockingStatus = fcntl(accountFileDescriptor, F_SETLKW, &lock);
        if (lockingStatus == -1)
        {
            perror("Error obtaining read lock on Account record!");
            return false;
        }

        readBytes = read(accountFileDescriptor, &ss, sizeof(struct student));
        if (readBytes == -1)
        {
            perror("Error while reading Account record from file!");
            return false;
        }

        lock.l_type = F_UNLCK;
        fcntl(accountFileDescriptor, F_SETLK, &lock);

        close(accountFileDescriptor);

        sn.id = ss.id + 1;
    }
       writeBytes = write(connFD, "Enter the name\n", 16);
       if (writeBytes == -1)
       {
         perror("Error writing NAME to client!");
         return false;
       }
       bzero(readBuffer, sizeof(readBuffer));
       readBytes = read(connFD, readBuffer, sizeof(readBuffer));
       if (readBytes == -1)
       {
        perror("Error reading name response from client!");
        return false;
       }

       strcpy(sn.name, readBuffer);

       bzero(writeBuffer, sizeof(writeBuffer));
       strcpy(writeBuffer, "Enter the age");
       writeBytes = write(connFD, writeBuffer, strlen(writeBuffer));
       if (writeBytes == -1)
       {
        perror("Error writing the AGE message to client!");
        return false;
       }

       bzero(readBuffer, sizeof(readBuffer));
       readBytes = read(connFD, readBuffer, sizeof(readBuffer));
       if (readBytes == -1)
       {
        perror("Error reading the age response from client!");
        return false;
       }

       int Age = atoi(readBuffer);
       if (Age == 0)
       {
        bzero(writeBuffer, sizeof(writeBuffer));
        strcpy(writeBuffer, "ERRON_INPUT_FOR_NUMBER");
        writeBytes = write(connFD, writeBuffer, strlen(writeBuffer));
        if (writeBytes == -1)
         {
            perror("Error while writing ERRON_INPUT_FOR_NUMBER message to client!");
            return false;
         }
        readBytes = read(connFD, readBuffer, sizeof(readBuffer)); // Dummy read
        return false;
        }
        sn.age = Age;

	bzero(writeBuffer, sizeof(writeBuffer));
       strcpy(writeBuffer, "number of courses student enroll");
       writeBytes = write(connFD, writeBuffer, strlen(writeBuffer));
       if (writeBytes == -1)
       {
        perror("Error writing the enroll message ");
        return false;
       }

       bzero(readBuffer, sizeof(readBuffer));
       readBytes = read(connFD, readBuffer, sizeof(readBuffer));
       if (readBytes == -1)
       {
        perror("Error reading the enroll response");
        return false;
       }

       int cou = atoi(readBuffer);
       
        sn.count = cou;

        sn.active = true;

        writeBytes = write(connFD, "Enter the username\n", 20);
        if (writeBytes == -1)
        {
         perror("Error writing USERNAME to client!");
         return false;
        }
        bzero(readBuffer, sizeof(readBuffer));
        readBytes = read(connFD, readBuffer, sizeof(readBuffer));
        if (readBytes == -1)
        {
         perror("Error reading username response from client!");
         return false;
        }

        strcpy(sn.login, readBuffer);

        writeBytes = write(connFD, "Enter the password\n", 20);
        if (writeBytes == -1)
        {
         perror("Error writing password to client!");
         return false;
        }
        bzero(readBuffer, sizeof(readBuffer));
        readBytes = read(connFD, readBuffer, sizeof(readBuffer));
        if (readBytes == -1)
        {
         perror("Error reading password response from client!");
         return false;
        }

        strcpy(sn.password, readBuffer);

        int studentFileDescriptor = open("student.txt", O_CREAT | O_APPEND | O_WRONLY, S_IRWXU);
        if (studentFileDescriptor == -1)
        {
         perror("Error while creating / opening  file!");
         return false;
        }
        writeBytes = write(studentFileDescriptor, &sn, sizeof(sn));
        if (writeBytes == -1)
        {
         perror("Error while writing record to file!");
         return false;
        }

       close(studentFileDescriptor);
       }
       bzero(writeBuffer, sizeof(writeBuffer));
       strcpy(writeBuffer, "added successfully");
       writeBytes = write(connFD, writeBuffer, strlen(writeBuffer));
       if (writeBytes == -1)
       {
        perror("Error sending loginID and password to the client!");
        return false;
       }

    if(type = 1)
    return pn.id;
    else return sn.id;
}

#endif

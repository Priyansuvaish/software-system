#include <stdio.h>
#include <errno.h>

#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/ip.h>

#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include "./ad.h"
#include "./prof.h"
#include "./student.h"
void connection_handler(int connFD);

void main()
{
    int sFD, sBS, sLS, cFD;
    struct sockaddr_in serverAddress, clientAddress;

    sFD = socket(AF_INET, SOCK_STREAM, 0);
    if (sFD == -1)
    {
        perror("server socket not created");
        _exit(0);
    }

    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(8081);
    serverAddress.sin_addr.s_addr = htonl(INADDR_ANY);

    sBS = bind(sFD, (struct sockaddr *)&serverAddress, sizeof(serverAddress));
    if (sBS == -1)
    {
        perror("binding failedserver socket!");
        _exit(0);
    }

    sLS = listen(sFD, 10);
    if (sLS == -1)
    {
        perror("listening for connections on the server socket is failed");
        close(sFD);
        _exit(0);
    }

    int clientSize;
    while (1)
    {
        clientSize = (int)sizeof(clientAddress);
        cFD = accept(sFD, (struct sockaddr *)&clientAddress, &clientSize);
        if (cFD == -1)
        {
            perror("connecting to client failed");
            close(sFD);
        }
        else
        {
            if (!fork())
            {
                connection_handler(cFD);
                close(cFD);
                _exit(0);
            }
        }
    }

    close(sFD);
}

void connection_handler(int connectionFileDescriptor)
{
    printf("Client has connected!\n");

    char readBuffer[1000], writeBuffer[1000];
    ssize_t readBytes, writeBytes;
    int userChoice;
    while(1)
 {
    char  start[]="\nwelcome to acadamia portal\nLogin as \nenter 1 for admin\nenter 2 for profeeser\nenter 3 for student";
    writeBytes = write(connectionFileDescriptor, start, strlen(start));
    if (writeBytes == -1)
        perror("Error while sending first prompt to the user!");
    else
    {
        bzero(readBuffer, sizeof(readBuffer));
        readBytes = read(connectionFileDescriptor, readBuffer, sizeof(readBuffer));
        if (readBytes == -1)
            perror("unabled to reading from client");
        else if (readBytes == 0)
            printf("No data is enter by the client");
        else
        {
            userChoice = atoi(readBuffer);
            switch (userChoice)
            {
            case 1:
                // Admin
                admin_operation_handler(connectionFileDescriptor);
		printf("close the connection to client!\n");
                return;
            case 2:
                // Customer
                customer_operation_handler(connectionFileDescriptor);
                printf("close the connection to client!\n");
                return;
            case 3: 
                student_operation_handler(connectionFileDescriptor);
                printf("close the connection to client!\n");
                return;
            default:
               writeBytes = write(connectionFileDescriptor, "incorrect option", 16);
                break;
            }
	 }
      }
   }
}

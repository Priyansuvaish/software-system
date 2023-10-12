#include <sys/ipc.h>
#include <sys/sem.h>


struct professor p;
int semIdentifier;
int add_course(int connFD);

void view_all_course(int connFD);
bool customer_operation_handler(int connFD)
{

    if (login_handler(2, connFD,&p,NULL))
    {
        ssize_t writeBytes, readBytes;            // Number of bytes read from / written to the client
        char readBuffer[1000], writeBuffer[1000]; // A buffer used for reading & writing to the client

        // Get a semaphore for the user
       key_t semKey = ftok("./professor.txt", p.id); // Generate a key based on the account number hence, different customers will have different semaphores

        union semun
        {
            int val; // Value of the semaphore
        } semSet;

        int semctlStatus;
        semIdentifier = semget(semKey, 1, 0); // Get the semaphore if it exists
        if (semIdentifier == -1)
        {
            semIdentifier = semget(semKey, 1, IPC_CREAT | 0700); // Create a new semaphore
            if (semIdentifier == -1)
            {
                perror("Error while creating semaphore!");
                _exit(1);
            }

            semSet.val = 1; // Set a binary semaphore
            semctlStatus = semctl(semIdentifier, 0, SETVAL, semSet);
            if (semctlStatus == -1)
            {
                perror("Error while initializing a binary sempahore!");
                _exit(1);
            }
        }
        bzero(writeBuffer, sizeof(writeBuffer));
        strcpy(writeBuffer, "FACULTY_LOGIN_SUCCESS");

    while (1)
        {
            strcat(writeBuffer, "\n");
            strcat(writeBuffer, "1. Add course\n2. remove offered course\n3. view offering course\n4. password change\n6. Exit");
            writeBytes = write(connFD, writeBuffer, strlen(writeBuffer));
            if (writeBytes == -1)
            {
                perror("Error while writing ADMIN_MENU to client!");
                return false;
            }
            bzero(writeBuffer, sizeof(writeBuffer));

            readBytes = read(connFD, readBuffer, sizeof(readBuffer));
            if (readBytes == -1)
            {
                perror("Error while reading client's choice for ADMIN_MENU");
                return false;
            }

            int choice = atoi(readBuffer);
            switch (choice)
            {
            case 1:
                 add_course(connFD);
                break;
            case 2:
  //               add_account(connFD,1);
                break;
            case 3: 
                view_all_course(connFD);
                break;
            case 4:
               
                break;
            case 5:
      //          delete_account(connFD);
                break;
            case 6:
   	    writeBytes = write(connFD, "professor logout", 16);
            connection_handler(connFD);
                 break;
            default:
                writeBytes = write(connFD, "incorrect option", 16);
                return false;
            }
        }
    }
    else
    {
        // ADMIN LOGIN FAILED
        return false;
    }
    return true;
}
int add_course(int connFD)
{
    ssize_t readBytes, writeBytes;
    char readBuffer[1000], writeBuffer[1000];
    struct Course c;
    writeBytes = write(connFD, "Enter the course name\n", 22);
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

       strcpy(c.name, readBuffer);
       c.id =p.id;

        int studentFileDescriptor = open("course.txt", O_CREAT | O_APPEND | O_WRONLY, S_IRWXU);
        if (studentFileDescriptor == -1)
        {
         perror("Error while creating / opening file!");
         return false;
        }
        writeBytes = write(studentFileDescriptor, &c, sizeof(c));
        if (writeBytes == -1)
        {
         perror("Error while writing Customer record to file!");
         return false;
        }

       close(studentFileDescriptor);

       bzero(writeBuffer, sizeof(writeBuffer));
       strcpy(writeBuffer, "added successfully");
       writeBytes = write(connFD, writeBuffer, strlen(writeBuffer));
       if (writeBytes == -1)
       {
        perror("Error sending customer loginID and password to the client!");
        return false;
       }
return 1;
}
void view_all_course(int connFD){
     int i=0;
     char readBuffer[1000], writeBuffer[1000];
      ssize_t writeBytes, readBytes;
     int sD = open("course.txt", O_RDONLY);
        if (sD == -1)
        {
         perror("Error while creating / opening file!");
         return;
        }
	struct Course pp;
	 bzero(writeBuffer, sizeof(writeBuffer));
	 strcpy(writeBuffer,"course name\n");
         write(connFD, writeBuffer, strlen(writeBuffer));
        while(read(sD,&pp,sizeof(struct Course)))
        {
          if(p.id == pp.id)
	  {
            i=i+1;
  	    bzero(writeBuffer, sizeof(writeBuffer));
            sprintf(writeBuffer, "%s\n", pp.name);
    	    writeBytes = write(connFD, writeBuffer, strlen(writeBuffer));
	    lseek(sD,i*sizeof(struct Course),SEEK_SET);
	  }
        }
}

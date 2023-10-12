#include <sys/ipc.h>
#include <sys/sem.h>


struct student s;
int semIdentifier;
int view_all(int connFD);
bool student_operation_handler(int connFD)
{

    if (login_handler(3, connFD,NULL,&s))
    {
        ssize_t writeBytes, readBytes;            // Number of bytes read from / written to the client
        char readBuffer[1000], writeBuffer[1000]; // A buffer used for reading & writing to the client

        // Get a semaphore for the user
        key_t semKey = ftok("./professor.txt", s.id); 

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
        strcpy(writeBuffer, "STUDENT_LOGIN_SUCCESS");

while (1)
        {
            strcat(writeBuffer, "\n");
            strcat(writeBuffer, "1.view all course\n2. enroll new course\n3. drop course\n4. view enrolled course\n5. password change\n6. Exit");
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
                 view_all(connFD);
                break;
            case 2:
  //               add_account(connFD,1);
                break;
            case 3: 
    //            get_transaction_details(connFD, -1);
                break;
            case 4:
               
                break;
            case 5:
      //          delete_account(connFD);
                break;
            case 6:
                writeBytes = write(connFD, "student logout", 14);
                return false;
            default:
                writeBytes = write(connFD, "incorrect option", 16);
                break;
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

int view_all(int connFD)
{
 int i=0;
     char readBuffer[1000], writeBuffer[1000];
      ssize_t writeBytes, readBytes;
     int sD = open("course.txt", O_RDONLY);
        if (sD == -1)
        {
         perror("Error while creating / opening file!");
         return 0;
        }
        struct Course pp={0};
         bzero(writeBuffer, sizeof(writeBuffer));
         strcpy(writeBuffer,"course name\tfaculty name\n");
         write(connFD, writeBuffer, strlen(writeBuffer));

        while(read(sD,&pp,sizeof(struct Course))>0)
        {
            i=i+1;
	    if(pp.active){
            bzero(writeBuffer, sizeof(writeBuffer));
            sprintf(writeBuffer, "%s\t\t%s\n", pp.name,pp.facultyname);
            writeBytes = write(connFD, writeBuffer, strlen(writeBuffer));}
         lseek(sD , i * sizeof(struct Course) , SEEK_SET);
        }
    return 1;
}

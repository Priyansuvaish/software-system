#include <sys/ipc.h>
#include <sys/sem.h>


bool change_password(int connFD);
struct professor pr={0};
int semIdentifier;
int add_course(int connFD);
int semIdentifier;
int view_all_course(int connFD);
bool customer_operation_handler(int connFD)
{

    if (login_handler(2, connFD,&pr,NULL))
    {
        ssize_t writeBytes, readBytes;            // Number of bytes read from / written to the client
        char readBuffer[1000], writeBuffer[1000]; // A buffer used for reading & writing to the client

        // Get a semaphore for the user
       key_t semKey = ftok("./professor.txt", pr.id);

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
                change_password(connFD);
                break;
            case 5:
      //          delete_account(connFD);
                break;
            case 6:
   	    writeBytes = write(connFD, "professor logout", 16);
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
int add_course(int connFD)
{
    ssize_t readBytes, writeBytes;
    char readBuffer[1000], writeBuffer[1000];
    struct Course c={0};
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
       strcpy(c.facultyname, pr.name);
       c.active= true;
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
int view_all_course(int connFD){
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
	 strcpy(writeBuffer,"course name\n");
         write(connFD, writeBuffer, strlen(writeBuffer));

        while(read(sD,&pp,sizeof(struct Course))>0)
        {
          if(strcmp(pr.name, pp.facultyname)  ==0)
	  {
	    if(pp.active){
            i=i+1;
  	    bzero(writeBuffer, sizeof(writeBuffer));
            sprintf(writeBuffer, "%s\n", pp.name);
    	    writeBytes = write(connFD, writeBuffer, strlen(writeBuffer));
	  }}
	 lseek(sD , i * sizeof(struct Course) , SEEK_SET);
        }
    return 1;
}
bool change_password(int connFD)
{
    ssize_t readBytes, writeBytes;
    char readBuffer[1000], writeBuffer[1000], hashedPassword[1000];

    char newPassword[1000];

    // Lock the critical section
    struct sembuf semOp = {0, -1, SEM_UNDO};
    int semopStatus = semop(semIdentifier, &semOp, 1);
    if (semopStatus == -1)
    {
        perror("Error while locking critical section");
        return false;
    }

        // Password matches with old password
        writeBytes = write(connFD, "ENTER NEW PASSWORD", 18);
        if (writeBytes == -1)
        {
            perror("Error writing PASSWORD_CHANGE_NEW_PASS message to client!");
            semOp.sem_op = 1;
            semop(semIdentifier, &semOp, 1);
            return false;
        }
        bzero(readBuffer, sizeof(readBuffer));
        readBytes = read(connFD, readBuffer, sizeof(readBuffer));
        if (readBytes == -1)
        {
            perror("Error reading new password response from client");
            semOp.sem_op = 1;
            semop(semIdentifier, &semOp, 1);
            return false;
        }

        strcpy(newPassword, readBuffer);

        writeBytes = write(connFD, "REENTER NEW PASSWORD", 20);
        if (writeBytes == -1)
        {
            perror("Error writing PASSWORD_CHANGE_NEW_PASS_RE message to client!");
            semOp.sem_op = 1;
            semop(semIdentifier, &semOp, 1);
            return false;
        }
        bzero(readBuffer, sizeof(readBuffer));
        readBytes = read(connFD, readBuffer, sizeof(readBuffer));
        if (readBytes == -1)
        {
            perror("Error reading new password reenter response from client");
            semOp.sem_op = 1;
            semop(semIdentifier, &semOp, 1);
            return false;
        }

        if (strcmp(readBuffer, newPassword) == 0)
        {
            // New & reentered passwords match

            strcpy(pr.password, newPassword);

            int customerFileDescriptor = open("./professor.txt", O_WRONLY);
            if (customerFileDescriptor == -1)
            {
                perror("Error opening customer file!");
                semOp.sem_op = 1;
                semop(semIdentifier, &semOp, 1);
                return false;
            }

            off_t offset = lseek(customerFileDescriptor, pr.id * sizeof(struct professor), SEEK_SET);
            if (offset == -1)
            {
                perror("Error seeking to the customer record!");
                semOp.sem_op = 1;
            semop(semIdentifier, &semOp, 1);
                return false;
            }

            struct flock lock = {F_WRLCK, SEEK_SET, offset, sizeof(struct professor), getpid()};
            int lockingStatus = fcntl(customerFileDescriptor, F_SETLKW, &lock);
            if (lockingStatus == -1)
            {
                perror("Error obtaining write lock on customer record!");
                semOp.sem_op = 1;
            semop(semIdentifier, &semOp, 1);
                return false;
            }

            writeBytes = write(customerFileDescriptor, &pr, sizeof(struct professor));
            if (writeBytes == -1)
            {
                perror("Error storing updated customer password into customer record!");
                semOp.sem_op = 1;
            semop(semIdentifier, &semOp, 1);
                return false;
            }

            lock.l_type = F_UNLCK;
            lockingStatus = fcntl(customerFileDescriptor, F_SETLK, &lock);

            close(customerFileDescriptor);

            writeBytes = write(connFD, "PASSWORD_CHANGE_SUCCESS", 23);
            readBytes = read(connFD, readBuffer, sizeof(readBuffer)); // Dummy read

            semOp.sem_op = 1;
            semop(semIdentifier, &semOp, 1);

            return true;
        }
        else
        {
            // New & reentered passwords don't match
            writeBytes = write(connFD, "REENTER_PASSWORD_INVALID_NOT_MATCHED", 36);
            //readBytes = read(connFD, readBuffer, sizeof(readBuffer)); // Dummy read
        }
    
    return false;
}

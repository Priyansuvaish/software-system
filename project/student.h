#include <sys/ipc.h>
#include <sys/sem.h>


struct student s;
int semIdentifier;
int view_all(int connFD);
bool enroll(int connFD);
int view_enroll(int connFD);
bool changepassword(int connFD);
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
                enroll(connFD);
                break;
            case 3: 
    //            get_transaction_details(connFD, -1);
                break;
            case 4:
               view_enroll(connFD);
                break;
            case 5:
                changepassword(connFD);
                break;
            case 6:
                return true;
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
int view_enroll(int connFD)
{
 int i=0;
     char readBuffer[1000], writeBuffer[1000];
      ssize_t writeBytes, readBytes;
     int sD = open("enroll.txt", O_RDONLY);
        if (sD == -1)
        {
         perror("Error while creating / opening file!");
         return 0;
        }
        struct enroll pp={0};
         bzero(writeBuffer, sizeof(writeBuffer));
         strcpy(writeBuffer,"course name\tfaculty name\n");
         write(connFD, writeBuffer, strlen(writeBuffer));

        while(read(sD,&pp,sizeof(struct enroll))>0)
        {
            i=i+1;
	    if(pp.active){
            bzero(writeBuffer, sizeof(writeBuffer));
            sprintf(writeBuffer, "%s\t\t%s\n", pp.name,pp.facultyname);
            writeBytes = write(connFD, writeBuffer, strlen(writeBuffer));}
         lseek(sD , i * sizeof(struct enroll) , SEEK_SET);
        }
    return 1;
}
bool enroll(int connFD){
    ssize_t readBytes, writeBytes;
    char readBuffer[1000], writeBuffer[1000];
    struct enroll e;
    struct Course pp;
    int i=0;
    off_t off;
    bool coursefind = false;
    // Lock the critical section
    struct sembuf semOp = {0, -1, SEM_UNDO};
    int semopStatus = semop(semIdentifier, &semOp, 1);
    if (semopStatus == -1)
    {
        perror("Error while locking critical section");
        return false;
    }
    writeBytes = write(connFD, "ENTER course name", 17);
        if (writeBytes == -1)
        {
            perror("Error writing course name");
            semOp.sem_op = 1;
            semop(semIdentifier, &semOp, 1);
            return false;
        }
        bzero(readBuffer, sizeof(readBuffer));
        readBytes = read(connFD, readBuffer, sizeof(readBuffer));
        if (readBytes == -1)
        {
            perror("Error reading course name");
            semOp.sem_op = 1;
            semop(semIdentifier, &semOp, 1);
            return false;
        }

    int FileDescriptor = open("./course.txt", O_RDWR);
            if (FileDescriptor == -1)
            {
                perror("Error opening course file!");
                semOp.sem_op = 1;
                semop(semIdentifier, &semOp, 1);
                return false;
            }
      while(read(FileDescriptor,&pp,sizeof(struct Course))>0)
        {
            i=i+1;
            if(strcmp(pp.name,readBuffer) == 0){
             if(pp.active && pp.enrol < pp.total){
		coursefind = true;
                strcpy(e.name,pp.name);
		strcpy(e.facultyname,pp.facultyname);
		strcpy(e.studentname,s.name);
		e.active = true;
		break;
	    }
	  }
         off = lseek(FileDescriptor , i * sizeof(struct Course) , SEEK_SET);
        }
	if(coursefind){
	  if(s.count > 0){
	    int customerFileDescriptor = open("./student.txt", O_WRONLY);
            if (customerFileDescriptor == -1)
            {
                perror("Error opening student file!");
                semOp.sem_op = 1;
                semop(semIdentifier, &semOp, 1);
                return false;
            }

            off_t offset = lseek(customerFileDescriptor, s.id * sizeof(struct student), SEEK_SET);
            if (offset == -1)
            {
                perror("Error seeking to the student record!");
                semOp.sem_op = 1;
            semop(semIdentifier, &semOp, 1);
                return false;
            }

            struct flock lock = {F_WRLCK, SEEK_SET, offset, sizeof(struct student), getpid()};
            int lockingStatus = fcntl(customerFileDescriptor, F_SETLKW, &lock);
            if (lockingStatus == -1)
            {
                perror("Error obtaining write lock on student record!");
                semOp.sem_op = 1;
            semop(semIdentifier, &semOp, 1);
                return false;
            }
	    s.count = s.count - 1;

            writeBytes = write(customerFileDescriptor, &s, sizeof(struct student));
            if (writeBytes == -1)
            {
                perror("Error storing student count");
                semOp.sem_op = 1;
            semop(semIdentifier, &semOp, 1);
                return false;
            }

            lock.l_type = F_UNLCK;
            lockingStatus = fcntl(customerFileDescriptor, F_SETLK, &lock);

            close(customerFileDescriptor);


	    struct flock loc = {F_WRLCK, SEEK_SET, off, sizeof(struct Course), getpid()};
            int locking = fcntl(FileDescriptor, F_SETLKW, &loc);
            if (locking == -1)
            {
                perror("Error obtaining write lock on student record!");
                semOp.sem_op = 1;
            semop(semIdentifier, &semOp, 1);
                return false;
            }
            pp.enrol = pp.enrol + 1;

            writeBytes = write(FileDescriptor, &pp, sizeof(struct Course));
            if (writeBytes == -1)
            {
                perror("Error storing student count");
                semOp.sem_op = 1;
            semop(semIdentifier, &semOp, 1);
                return false;
            }

            lock.l_type = F_UNLCK;
            lockingStatus = fcntl(FileDescriptor, F_SETLK, &lock);

            close(FileDescriptor);


	   int enrollFileDescriptor = open("enroll.txt", O_CREAT | O_APPEND | O_WRONLY, S_IRWXU);
        if (enrollFileDescriptor == -1)
        {
         perror("Error while creating / opening file!");
         return false;
        }
        writeBytes = write(enrollFileDescriptor, &e, sizeof(e));
        if (writeBytes == -1)
        {
         perror("Error while writing  record to file!");
         return false;
        }

       close(enrollFileDescriptor);

		bzero(writeBuffer, sizeof(writeBuffer));
       		strcpy(writeBuffer, "enroll successfully");
       		writeBytes = write(connFD, writeBuffer, strlen(writeBuffer));
       if (writeBytes == -1)
       {
        perror("Error sending enrool message");
        return false;
       }

	  }
	  else{
		writeBytes = write(connFD, "course enrolled finished", 24);return false;
	 }
	}
        else{
	    writeBytes = write(connFD, "either course seat are full or course in not exist", 50);return false;
	}
	return true;
}
bool changepassword(int connFD)
{
    ssize_t readBytes, writeBytes;
    char readBuffer[1000], writeBuffer[1000];

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

            strcpy(s.password, newPassword);

            int customerFileDescriptor = open("./student.txt", O_WRONLY);
            if (customerFileDescriptor == -1)
            {
                perror("Error opening customer file!");
                semOp.sem_op = 1;
                semop(semIdentifier, &semOp, 1);
                return false;
            }

            off_t offset = lseek(customerFileDescriptor, s.id * sizeof(struct student), SEEK_SET);
            if (offset == -1)
            {
                perror("Error seeking to the customer record!");
                semOp.sem_op = 1;
            semop(semIdentifier, &semOp, 1);
                return false;
            }

            struct flock lock = {F_WRLCK, SEEK_SET, offset, sizeof(struct student), getpid()};
            int lockingStatus = fcntl(customerFileDescriptor, F_SETLKW, &lock);
            if (lockingStatus == -1)
            {
                perror("Error obtaining write lock on customer record!");
                semOp.sem_op = 1;
            semop(semIdentifier, &semOp, 1);
                return false;
            }
	    writeBytes = write(customerFileDescriptor, &s, sizeof(struct student));
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

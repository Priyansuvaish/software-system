#include "./function.h"
bool get_account_details(int connFD,int type, struct professor  *p,struct student *s);
bool admin_operation_handler(int connFD)
{

    if (login_handler(1, connFD,NULL,NULL))
    {
        ssize_t writeBytes, readBytes;            // Number of bytes read from / written to the client
        char readBuffer[1000], writeBuffer[1000]; // A buffer used for reading & writing to the client
        bzero(writeBuffer, sizeof(writeBuffer));
        strcpy(writeBuffer, "ADMIN_LOGIN_SUCCESS");

while (1)
        {
            strcat(writeBuffer, "\n");
            strcat(writeBuffer, "1. Add Student\n2. Add Faculty\n3. view professor details\n4. view student details\n6. Exit");
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
                 add_account(connFD,2);
                break;
            case 2:
                 add_account(connFD,1);
                break;
            case 3: 
                get_account_details(connFD,1, NULL,NULL);
                break;
            case 4:
                 get_account_details(connFD,2, NULL,NULL);
                break;
            case 5:
      //          delete_account(connFD);
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


bool get_account_details(int connFD,int type, struct professor  *p,struct student *s)
{
    ssize_t readBytes, writeBytes;            // Number of bytes read from / written to the socket
    char readBuffer[1000], writeBuffer[1000]; // A buffer for reading from / writing to the socket
    char tempBuffer[1000];

    int id;
    struct professor account;
    struct student acc;
    int accountFileDescriptor;

    if (p == NULL && s==NULL)
    {

        writeBytes = write(connFD, "enter the id\n", 14);
        if (writeBytes == -1)
        {
            perror("Error writing GET_ACCOUNT_NUMBER message to client!");
            return false;
        }

        bzero(readBuffer, sizeof(readBuffer));
        readBytes = read(connFD, readBuffer, sizeof(readBuffer));
        if (readBytes == -1)
        {
            perror("Error reading account number response from client!");
            return false;
        }

        id = atoi(readBuffer);
    }
    else if(p!=NULL)
        id = p->id;
    else id = s->id;
    if(type ==1){
    accountFileDescriptor = open("./professor.txt", O_RDONLY);
    if (accountFileDescriptor == -1)
    {
        // Account record doesn't exist
        bzero(writeBuffer, sizeof(writeBuffer));
        strcpy(writeBuffer, "ID_DOESNT_EXIT");
        strcat(writeBuffer, "^");
        perror("Error opening account file in get_account_details!");
        writeBytes = write(connFD, writeBuffer, strlen(writeBuffer));
        if (writeBytes == -1)
        {
            perror("Error while writing ACCOUNT_ID_DOESNT_EXIT message to client!");
            return false;
        }
        readBytes = read(connFD, readBuffer, sizeof(readBuffer)); // Dummy read
        return false;
    }
    int offset = lseek(accountFileDescriptor, id * sizeof(struct professor), SEEK_SET);
    if (offset == -1 && errno == EINVAL)
    {
        // Account record doesn't exist
        bzero(writeBuffer, sizeof(writeBuffer));
        strcpy(writeBuffer, "ACCOUNT_ID_DOESNT_EXIT");
        strcat(writeBuffer, "^");
        perror("Error seeking to account record in get_account_details!");
        writeBytes = write(connFD, writeBuffer, strlen(writeBuffer));
        if (writeBytes == -1)
        {
            perror("Error while writing ACCOUNT_ID_DOESNT_EXIT message to client!");
            return false;
        }
        readBytes = read(connFD, readBuffer, sizeof(readBuffer)); // Dummy read
        return false;
    }
    else if (offset == -1)
    {
        perror("Error while seeking to required account record!");
        return false;
    }

    struct flock lock = {F_RDLCK, SEEK_SET, offset, sizeof(struct professor), getpid()};

    int lockingStatus = fcntl(accountFileDescriptor, F_SETLKW, &lock);
    if (lockingStatus == -1)
    {
        perror("Error obtaining read lock on account record!");
        return false;
    }

    readBytes = read(accountFileDescriptor, &account, sizeof(struct professor));
    if (readBytes == -1)
    {
        perror("Error reading account record from file!");
        return false;
    }

    lock.l_type = F_UNLCK;
    fcntl(accountFileDescriptor, F_SETLK, &lock);

    if (p != NULL)
    {
        *p = account;
        return true;
    }

    bzero(writeBuffer, sizeof(writeBuffer));
    sprintf(writeBuffer, "Account Details - \n\tID : %d\n\tNAME : %s\n\tAGE : %d", account.id, account.name, account.age);
    
    writeBytes = write(connFD, writeBuffer, strlen(writeBuffer));
//    readBytes = read(connFD, readBuffer, sizeof(readBuffer)); // Dummy read
   }
   if(type ==2)
  {
    accountFileDescriptor = open("./student.txt", O_RDONLY);
    if (accountFileDescriptor == -1)
    {
        // Account record doesn't exist
        bzero(writeBuffer, sizeof(writeBuffer));
        strcpy(writeBuffer, "ID_DOESNT_EXIT");
        strcat(writeBuffer, "^");
        perror("Error opening account file in get_account_details!");
        writeBytes = write(connFD, writeBuffer, strlen(writeBuffer));
        if (writeBytes == -1)
        {
            perror("Error while writing ACCOUNT_ID_DOESNT_EXIT message to client!");
            return false;
        }
        readBytes = read(connFD, readBuffer, sizeof(readBuffer)); // Dummy read
        return false;
    }
    int offset = lseek(accountFileDescriptor, id * sizeof(struct student), SEEK_SET);
    if (offset == -1 && errno == EINVAL)
    {
        // Account record doesn't exist
        bzero(writeBuffer, sizeof(writeBuffer));
        strcpy(writeBuffer, "ACCOUNT_ID_DOESNT_EXIT");
        strcat(writeBuffer, "^");
        perror("Error seeking to account record in get_account_details!");
        writeBytes = write(connFD, writeBuffer, strlen(writeBuffer));
        if (writeBytes == -1)
        {
            perror("Error while writing ACCOUNT_ID_DOESNT_EXIT message to client!");
            return false;
        }
        readBytes = read(connFD, readBuffer, sizeof(readBuffer)); // Dummy read
        return false;
    }
    else if (offset == -1)
    {
        perror("Error while seeking to required account record!");
        return false;
    }

    struct flock lock = {F_RDLCK, SEEK_SET, offset, sizeof(struct student), getpid()};

    int lockingStatus = fcntl(accountFileDescriptor, F_SETLKW, &lock);
    if (lockingStatus == -1)
    {
        perror("Error obtaining read lock on account record!");
        return false;
    }

    readBytes = read(accountFileDescriptor, &acc, sizeof(struct student));
    if (readBytes == -1)
    {
        perror("Error reading account record from file!");
        return false;
    }

    lock.l_type = F_UNLCK;
    fcntl(accountFileDescriptor, F_SETLK, &lock);

    if (s != NULL)
    {
        *s = acc;
        return true;
    }

    bzero(writeBuffer, sizeof(writeBuffer));
    sprintf(writeBuffer, "Account Details - \n\tID : %d\n\tNAME : %s\n\tAGE : %d\n\tStatus : %d", acc.id, acc.name, acc.age,acc.active);
    
    writeBytes = write(connFD, writeBuffer, strlen(writeBuffer));
//    readBytes = read(connFD, readBuffer, sizeof(readBuffer)); // Dummy read
   }
    return true;
}

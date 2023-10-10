
struct professor p;
bool customer_operation_handler(int connFD)
{

    if (login_handler(2, connFD,&p,NULL))
    {
        ssize_t writeBytes, readBytes;            // Number of bytes read from / written to the client
        char readBuffer[1000], writeBuffer[1000]; // A buffer used for reading & writing to the client

        // Get a semaphore for the user
        key_t semKey = ftok(CUSTOMER_FILE, loggedInCustomer.account); // Generate a key based on the account number hence, different customers will have different semaphores

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
            strcat(writeBuffer, "1.Add course\n2. remove offered course\n3. view enrollment\n4. password change\n5. Exit");
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
//                 add_account(connFD,2);
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
        //        modify_customer_info(connFD);
                break;
            default:
                writeBytes = write(connFD, "ADMIN_LOGOUT", 12);
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


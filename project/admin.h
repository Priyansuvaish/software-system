#include "./function.h"
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
            strcat(writeBuffer, "1.Add Student\n2. Add Faculty\n3. Activate/Deactivate Student\n4. Update Student/Faculty details\n5. Exit");
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


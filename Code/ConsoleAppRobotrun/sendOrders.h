#ifndef SENDORDERS_H_INCLUDED
#define SENDORDERS_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <stdio.h>
#include <time.h>
#include <string.h>
#include <windows.h>

char myPort[10];

void delay(int milsec)
{
    clock_t startTime = clock();
    while(clock() < (startTime + milsec));
}

HANDLE open_com_port(char* port, int baudrate) {
    HANDLE hComm;
    char com[50];
    sprintf(com, "\\\\.\\%s", port); // Add prefix to COM port name for Windows

    hComm = CreateFile(com, GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, 0, NULL);
    if (hComm == INVALID_HANDLE_VALUE) {
        printf("Error opening COM port.\n");
        return NULL;
    }

    DCB dcbSerialParams = { 0 };
    dcbSerialParams.DCBlength = sizeof(dcbSerialParams);
    if (!GetCommState(hComm, &dcbSerialParams)) {
        printf("Error getting state.\n");
        CloseHandle(hComm);
        return NULL;
    }

    dcbSerialParams.BaudRate = baudrate;
    dcbSerialParams.ByteSize = 8;
    dcbSerialParams.StopBits = ONESTOPBIT;
    dcbSerialParams.Parity = NOPARITY;

    if (!SetCommState(hComm, &dcbSerialParams)) {
        printf("Error setting serial port state.\n");
        CloseHandle(hComm);
        return NULL;
    }

    return hComm;
}

int send_hex_over_com_port(HANDLE hComm, int value) {
    char buffer[50];
    sprintf(buffer, "%02X", value);
    DWORD dwBytesWritten = 0;
    BOOL fSuccess;
    fSuccess = WriteFile(hComm, buffer, strlen(buffer), &dwBytesWritten, NULL);
    if (!fSuccess) {
        printf("Error writing to COM port.\n");
        return -1;
    }
    return dwBytesWritten;
}

int readArrow() {
    int ch;
    while(1)
    {
        ch = getch();
        if(ch == 27) // escape key was pressed
        {
            return 4;
            break;
        }
        else if(ch == 98)// b was pressed
        {
            return 5;
            break;
        }
        else if(ch == 224) // arrow key was pressed
        {
            ch = getch(); // read the next character
            switch (ch) {
                case 72: // up arrow key
                    return 0;
                    break;
                case 80: // down arrow key
                    return 1;
                    break;
                case 75: // left arrow key
                    return 2;
                    break;
                case 77: // right arrow key
                    return 3;
                    break;
            }
        }
        if(ch == 0)
        {
            return 5;
        }
        ch = 0;
    }
}

int sendSerialHex(int value)
{
    //char port[] = "COM21";
    int baudrate = 9600;
    HANDLE hComm = open_com_port(myPort, baudrate);
    if (hComm == NULL)
    {
        printf("Error opening COM port.\n");
        return -1;
    }

    //int value = 0xFF;
    int n = send_hex_over_com_port(hComm, value);
    if (n == -1)
    {
        printf("Error sending hex value over COM port.\n");
        return -1;
    }

    printf("Sent %d bytes: 0x%X\n", n, value); //debug monitor for testing which bytes are sent

    CloseHandle(hComm);
}

int sendOrders(void)
{
    int orderCount = 0;
    int xCoords[32];
    int yCoords[32];

    while(1)
    {

        system("cls");
        printf("Geef het aantal bestellingen: ");
        scanf("%d", &orderCount);

        for(int i = 0; i < orderCount; i++)
        {
            scanf("%d, %d", &xCoords[i], &yCoords[i]);
        }

        system("cls");

        for(int i = 0; i < orderCount; i++)
        {
            printf("Order #%i --> ( %d , %d )\n", i, xCoords[i], yCoords[i]);
        }
        sendSerialHex(0x01); // tell robot so get ready for receiving orders
        printf("bestellingen verzenden...\n");

        //delay(200);
        sendSerialHex(orderCount);
        for(int i = 0; i < orderCount; i++)
        {
            sendSerialHex(xCoords[i]);
            sendSerialHex(yCoords[i]);
            //delay(20);
        }
        printf("Nog een bestelling doen?\n1:ja\n2:keer terug naar menu");
        int selection = getch();
        if(selection == 49)
        {
            return 1;
        }
        else if(selection == 50)
        {
            return 0;
        }
    }
    return 0;
}

int manualDrive(void)
{

    int control = readArrow();
        if(control == 0) //Arrow up
        {
            sendSerialHex(0x01);
            return 1;
        }
        else if(control == 1) //Arrow down
        {
            sendSerialHex(0x02);
            return 1;
        }
        else if(control == 2) //Arrow left
        {
            sendSerialHex(0x03);
            return 1;
        }
        else if(control == 3) //Arrow right
        {
            sendSerialHex(0x04);
            return 1;
        }
         else if(control == 4) // Escape
        {
            sendSerialHex(0x06);
            return 0;
        }
        else if(control == 5) //b
        {
            sendSerialHex(0x05);
            return 1;
        }
}

int batteryMenu(void)
{
    //system("cls");


    //sendSerialHex(0x03);
    while(1)
    {
        int ch = getch();
        switch(ch)
        {
            case 49:
                sendSerialHex(0x03);
                sendSerialHex(0x01);
                break;
            case 50:
                sendSerialHex(0x03);
                sendSerialHex(0x02);
                break;
            case 51:
                sendSerialHex(0x03);
                sendSerialHex(0x03);
                break;
            case 52:
                sendSerialHex(0x03);
                sendSerialHex(0x04);
                break;
            case 53:
                sendSerialHex(0x03);
                sendSerialHex(0x05);
                break;
            case 54:
                sendSerialHex(0x03);
                sendSerialHex(0x06);
                break;
            case 55:
                sendSerialHex(0x03);
                sendSerialHex(0x07);
                break;
            case 56:
                sendSerialHex(0x03);
                sendSerialHex(0x08);
                break;
            case 57:
                sendSerialHex(0x03);
                sendSerialHex(0x09);
                break;


        }
        printf("druk op een willekeurige knop on terug te keren naar het menu");
        getch();
        return 0;

    }
}

int spinSim()
{

    while(1)
    {
        int ch = getch();
        switch(ch)
        {
            case 49:
                sendSerialHex(0x04);
                break;

            case 50:
                sendSerialHex(0xFF);
                return 0;
                break;



        }
    }
}




#endif // SENDORDERS_H_INCLUDED

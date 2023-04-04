#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <string.h>

int write_to_com_port(char* port, int baudrate, char* data) {
    HANDLE hSerial;
    DCB dcbSerialParams = {0};
    COMMTIMEOUTS timeouts = {0};

    // Open COM port
    hSerial = CreateFile(port, GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
    if (hSerial == INVALID_HANDLE_VALUE) {
        printf("Error opening COM port\n");
        return 1;
    }

    // Set COM port parameters
    dcbSerialParams.DCBlength = sizeof(dcbSerialParams);
    if (!GetCommState(hSerial, &dcbSerialParams)) {
        printf("Error getting state of COM port\n");
        CloseHandle(hSerial);
        return 1;
    }
    dcbSerialParams.BaudRate = baudrate;
    dcbSerialParams.ByteSize = 8;
    dcbSerialParams.StopBits = ONESTOPBIT;
    dcbSerialParams.Parity = NOPARITY;
    if (!SetCommState(hSerial, &dcbSerialParams)) {
        printf("Error setting state of COM port\n");
        CloseHandle(hSerial);
        return 1;
    }

    // Set COM port timeouts
    timeouts.ReadIntervalTimeout = 50;
    timeouts.ReadTotalTimeoutConstant = 50;
    timeouts.ReadTotalTimeoutMultiplier = 10;
    timeouts.WriteTotalTimeoutConstant = 50;
    timeouts.WriteTotalTimeoutMultiplier = 10;
    if (!SetCommTimeouts(hSerial, &timeouts)) {
        printf("Error setting timeouts of COM port\n");
        CloseHandle(hSerial);
        return 1;
    }

    // Write data to COM port
    DWORD bytesWritten;
    if (!WriteFile(hSerial, data, strlen(data), &bytesWritten, NULL)) {
        printf("Error writing data to COM port\n");
        CloseHandle(hSerial);
        return 1;
    }

    // Close COM port
    CloseHandle(hSerial);

    return 0;
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



int read_from_com_port(HANDLE hComm, char* buffer, int buffer_size) {
    DWORD dwBytesRead = 0;
    BOOL fSuccess;
    fSuccess = ReadFile(hComm, buffer, buffer_size, &dwBytesRead, NULL);
    if (!fSuccess) {
        printf("Error reading from COM port.\n");
        return -1;
    }
    return dwBytesRead;
}

/*int main() {
    char port[] = "COM9";


    int baudrate = 115200;

    while(1)
    {
        HANDLE hComm = open_com_port(port, baudrate);
        if (hComm == NULL) {
        printf("Error opening COM port.\n");
        return -1;
        }

        char buffer[1024];
        int n = read_from_com_port(hComm, buffer, 1024);
        if (n == -1) {
        printf("Error reading from COM port.\n");
        return -1;
        }


    printf("Read %d bytes: %s\n", n, buffer);

    CloseHandle(hComm);
    }
    return 0;
}*/

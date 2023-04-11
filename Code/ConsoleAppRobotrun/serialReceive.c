unsigned char read_one_byte(HANDLE hComm) {
    DWORD bytesRead;
    unsigned char buf;

    if (!ReadFile(hComm, &buf, 1, &bytesRead, NULL)) {
        printf("Failed to read from COM port\n");
        return 0;
    }

    return buf;
}

int serialReceive() {
    HANDLE hComm;
    unsigned char byte;

    // Open the COM port
    hComm = open_com_port("COM21", 9600);
    if (hComm == NULL) {
        return 1;
    }

    // Read one byte
    byte = read_one_byte(hComm);
    printf("Read byte: %02d\n", byte);

    // Close the COM port
    CloseHandle(hComm);

    return 0;
}

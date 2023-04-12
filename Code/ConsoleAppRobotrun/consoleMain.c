#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "readArrow.h"
#include "readArrow.c"
#include "readKeys.h"
#include "readKeys.c"
#include "leesInteger.h"
#include "leesInteger.c"
#include "serial.c"
#include "sendOrders.h"
#include "serialReceive.c"

// parts of this code are copied from the internet. These are opensource codes and are from: https://www.codeincodeblock.com/2011/03/move-console-windows-using-codeblock.html

HWND WINAPI GetConsoleWindowNT(void)
{
    //declare function pointer type
    typedef HWND WINAPI(*GetConsoleWindowT)(void);
    //declare one such function pointer
    GetConsoleWindowT GetConsoleWindow;
    //get a handle on kernel32.dll
    HMODULE hk32Lib = GetModuleHandle(TEXT("KERNEL32.DLL"));
    //assign procedure address to function pointer
    GetConsoleWindow = (GetConsoleWindowT)GetProcAddress(hk32Lib
    ,TEXT("GetConsoleWindow"));
    //check if the function pointer is valid
    //since the function is undocumented
    if(GetConsoleWindow == NULL){
        return NULL;
    }
    //call the undocumented function
    return GetConsoleWindow();
}

void resizeWindow()
{
    HWND hWnd=GetConsoleWindowNT();
    MoveWindow(hWnd,600,250,500,300,TRUE);
}

void delay(int second){

int milsec = 1000 * second;

clock_t startTime = clock();

while(clock() < (startTime + milsec));

}

void printInit()
{
    printf("------------- CONSOLE APPLICATIE ROBOTRUN -------------\n\n");
    printf("                          / \\\n");
    printf("                         // \\\\\n");
    printf("                        //   \\\\\n");
    printf("                       //     \\\\\n");
    printf("                       ||     ||\n");
    printf("                =======|| [ ] ||=======\n");
    printf("                \\\\     || [ ] ||     //\n");
    printf("                 \\\\====|| [ ] ||====//\n");
    printf("                       +++++++++\n");
    printf("                    // | | | | | \\\\\n\n");
    printf("-------------------------------------------------------\n\n");
}

void printMenu()
{
    printf("Menu:\n\n1. Ga naar het bestellingsmenu\n2. Ga naar afstandsbesturingsmenu\n");
}

void printManualMenu()
{
    printf("Afstandsbesturing:\n\npijltjestoetsen:\nBoven: vooruit/accelleratie\nOnder: achteruit/accelleratie\nLinks: draai linksom/accelleratie\nRechts: draai rechtsom/accelleratie\n\nDruk op toets 'b' om te remmen\n\nDruk tweemaal op escape om terug te keren naar het menu\n\n");
}

void printOrderMenu()
{
    printf("orders:\n\n");
}


int main(void)
{
    enum STATES{init, menu, manualOverride, orders};
    enum STATES state = menu;

    resizeWindow();

    printInit();
    delay(4);
    system("cls");
    while(1)
    {
        int selection;
        switch(state)
        {

            case menu:
                printMenu();
                //serialReceive();
                //serialReceive();
                selection = getch(); //reads the keyboard
                if(selection == 49) // "1" was pressed
                {
                    state = orders;
                }
                else if(selection == 50) // "2" was pressed
                {
                    state = manualOverride;
                }
                system("cls");
                break;

            case manualOverride:
                printManualMenu();
                while(manualDrive()) //manual drive returns 1, exept if the user presses esc to escape this menu.
                {

                }

                if(readArrow() == 4)
                {
                    state = menu;
                }
                system("cls");
                break;
            case orders:

                printOrderMenu();
                while(sendOrders())
                {

                }
                state = menu;
                system("cls");
                break;



        }

    }





    return 0;
}







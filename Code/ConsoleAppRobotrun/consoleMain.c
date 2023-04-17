#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "readArrow.h"
#include "readArrow.c"
#include "readKeys.h"
#include "readKeys.c"
#include "leesInteger.h"
#include "leesInteger.c"
#include "sendOrders.h"
#include "serialReceive.c"
#include "batterySimulation.h"


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
    printf("Menu:\n\n1. Ga naar het bestellingsmenu\n2. Ga naar afstandsbesturingsmenu\n3. Simuleer batterijpercentage\n4. Simuleer spin\n", '%');
}

void printManualMenu()
{
    printf("Afstandsbesturing:\n\npijltjestoetsen:\nBoven: vooruit/accelleratie\nOnder: achteruit/accelleratie\nLinks: draai linksom/accelleratie\nRechts: draai rechtsom/accelleratie\n\nDruk op toets 'b' om te remmen\n\nDruk tweemaal op escape om terug te keren naar het menu\n\n");
}

void printOrderMenu()
{
    printf("orders:\n\n");
}

void printBatterySimulation()
{
    printf("Batterijsimulatie:\nDruk op toets 1-9\nDeze staan voor percentages 10-90 procent.\n");
}

void printSpinning()
{
    printf("Spin menu:\n\n1. Simuleer spin\n2. Ga terug naar het menu\n");
}

int main(void)
{
    enum STATES{init, menu, manualOverride, orders, batterySimulation, spinning};
    enum STATES state = menu;

    resizeWindow();

    printInit();
    delay(2000);
    system("cls");
    printf("Voer hier de comport in als volgt: 'COMx'\n");
    fgets(myPort, sizeof(myPort), stdin);

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
                else if(selection == 51) // "3" was pressed
                {
                    state = batterySimulation;
                }
                else if(selection == 52) // "4" was pressed
                {
                    state = spinning;
                }
                system("cls");
                break;

            case manualOverride:

                printManualMenu();
                sendSerialHex(0x02);
                while(manualDrive()) //manual drive returns 1, except if the user presses escape to escape this menu.
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

            case batterySimulation:

                printBatterySimulation();
                while(batteryMenu())
                {

                }
                state = menu;
                system("cls");
                break;

            case spinning:

                printSpinning();
                while(spinSim())
                {

                }
                state = menu;
                system("cls");
                break;
        }

    }
    return 0;
}







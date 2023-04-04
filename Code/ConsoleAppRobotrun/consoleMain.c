#include <stdio.h>
#include "readArrow.h"
#include "readArrow.c"
#include "readKeys.h"
#include "readKeys.c"
#include "leesInteger.h"
#include "leesInteger.c"




int main(void)
{
    enum STATES{menu, manualOverride, orders};
    enum STATES state = menu;

    while(1)
    {
        int selection;
        switch(state)
        {

            case menu:
                printf("Menu:\n");
                selection = getch();
                if(selection == 49)
                {
                    state = orders;
                }
                else if(selection == 50)
                {
                    state = manualOverride;
                }
                system("cls");
                break;

            case manualOverride:
                printf("manualOverride:\n");
                if(readArrow() == 4)
                {
                    state = menu;
                }
                system("cls");
                break;
            case orders:
                printf("orders:\n");
                if(readArrow() == 4)
                {
                    state = menu;
                }
                system("cls");
                break;


        }

    }





    return 0;
}



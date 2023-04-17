#include <conio.h>
#include <stdio.h>
#include "readKeys.h"

int readKeys()
{
    int ch;
    while (1) {
            ch = getch(); // read the next character
            switch (ch) {
                case 1: // up arrow key
                    return 0;
                    break;
                case 2: // down arrow key
                    return 1;
                    break;
                case 3: // left arrow key
                    return 2;
                    break;
                case 4: // right arrow key
                    return 3;
                    break;
            }
    }
}

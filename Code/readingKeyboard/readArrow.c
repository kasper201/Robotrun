#include <conio.h>
#include <stdio.h>
#include "readArrow.h"

int readArrow() {
    int ch;
    while (1) {
        ch = getch();
        if (ch == 224) { // arrow key was pressed
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
    }
    //return 0;
}

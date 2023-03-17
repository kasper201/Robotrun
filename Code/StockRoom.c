#include <pololu/3pi.h>
#include <avr/pgmspace.h>
#include "StockRoom.h"

enum direction{minX, plusX, minY, plusY};
struct coords{int Xc, Yc, Xp, Yp, Xarray[30], Yarray[30]};
	
void stockroomStart()
{
	enum direction facing = minX;    //driveTill(Xp (all) = Xc)
	
}

void findPackage()
{
 
}

void passingToCharge()
{
	turn(1);
	
	turn(1);
}

#ifndef StockRoom_H_
#define StockRoom_H_

int packageAmount;

enum direction{minX, plusX, minY, plusY};
enum direction facing;

struct coords{int Xcurrent, Ycurrent, Xpackage, Ypackage;};
struct coords p1;

struct orders{int Xorders[32], Yorders[32]};
struct orders o1;

struct amount{int amountOfZero, amountOfOne, amountOfTwo, amountOfThree;};

void findPackageY()
void passingToCharge()
void stockroomRoutine()
void TurnBack()
void GetY()

#endif

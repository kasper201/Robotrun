#ifndef StockRoom_H_
#define StockRoom_H_

enum direction{minX, plusX, minY, plusY};
enum direction facing;

struct coords{int Xcurrent, Ycurrent, Xpackage;};
struct coords p1;

struct orders{int Xorders[32], Yorders[32];};
struct orders o1;

//struct amount{int amountOfZero, amountOfOne, amountOfTwo, amountOfThree;};

void stockroomRoutine();
void nextRound();
void findPackageX();
void findPackageY();
void TurnBack();

#endif

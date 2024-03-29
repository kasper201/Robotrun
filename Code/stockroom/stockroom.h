#ifndef StockRoom_H_
#define StockRoom_H_

enum direction{minX, plusX, minY, plusY};
enum direction facing;

struct coords{int Xcurrent, Ycurrent, Xpackage, Ypackage;};
struct coords p1;

struct orders{int Xorders[32], Yorders[32], packageAmount;};
struct orders o1;

void stockroomRoutine();
void findPackage();
void TurnBack();
void turnToY();
void turnToX();

#endif

#ifndef FINDLINE_H_
#define FINDLINE_H_

int crossing = 0;

void initRobot();
void startDrivingAfter();
void followLine(int *typeOfCrossing, int inMaze);
void turn(int turnTo);

#endif // FINDLINE

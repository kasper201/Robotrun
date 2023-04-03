#ifndef FINDLINE_H_
#define FINDLINE_H_

void initRobot();
void startDrivingAfter();
void followLine(int *typeOfCrossing, int inMaze);
void turn(int turnTo);
void followCharge(int *endPointReached);
void spin();

#endif // FINDLINE

/*

Movement steps are defined as an array of legmovements, foreach joint (servo).
Since each leg has 3 joints (servo's) and the hexapod has 6 legs it needs 18 servo instructions per step.
*/

#ifndef HEXASPODTRUCT_H
#define HEXASPODTRUCT_H

#include "arduino.h";
struct LegMovement
{
  byte s1; // near body along z-axis 
  byte s2; // near body
  byte s3; // mid leg
};

struct PodMovementStep
{
  LegMovement L1; // Left front leg
  LegMovement R1; // right front lef
  LegMovement L2; // mid left leg
  LegMovement R2; // mid right leg
  LegMovement L3; // aft left leg
  LegMovement R3; // aft right leg
};

struct point
{
  point(int xValue, int yValue, int zValue)
  {
    this->x = xValue;
    this->y = yValue;
    this->z = zValue;
  }

  int x;
  int y;
  int z;
};

struct endpoints
{
  endpoints(point* p1Value, point* p2Value, point* p3Value, point* p4Value, point* p5Value, point* p6Value)
  {
    this->p1 = p1Value;
    this->p2 = p2Value;
    this->p3 = p3Value;
    this->p4 = p4Value;
    this->p5 = p5Value;
    this->p6 = p6Value;
  }

  point* p1;
  point* p2;
  point* p3;
  point* p4;
  point* p5;
  point* p6;
};



#endif



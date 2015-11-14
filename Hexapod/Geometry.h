/*
* Definition of the hexapod geometry.
*/

#ifndef GEOMETRY_H
#define GEOMETRY_H

#include "HexapodStruct.h";

// definition of the leg positions from the center of the body (0, 0, 0)
point* P1 = new point(-56, 31, 40);
point* P2 = new point(0, 42, 40);
point* P3 = new point(56, 42, 40);
point* P4 = new point(-56, -31, 40);
point* P5 = new point(0, -42, 40);
point* P6 = new point(56, -42, 40);

int zBody = 40; // body height  in resting position

#endif

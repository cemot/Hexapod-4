
/*
Defines the walking patterns
*/

#ifndef MOVEMENT_H
#define MOVEMENT_H

#include "HexapodStruct.h";

LegMovement lmWait = { 0, 0, 0 };
LegMovement lmLiftLeg2 = { 0, 1, 0 }; // lift using 2nd servo
LegMovement lmLiftLeg3 = { 0, 0, 1 }; // lift using 3rd servo
LegMovement lmLowerLeg2 = { 0, -1, 0 }; // lift using 2nd servo
LegMovement lmLowerLeg3 = { 0, 0, -1 }; // lift using 3rd servo
LegMovement lmForward = { 1, 0, 0 };
LegMovement lmBackward = { -1, 0, 0 };

PodMovementStep WaitMovement[] = {
 { 
    lmWait, lmWait,
    lmWait,lmWait,
    lmWait,lmWait,
  }
 };

/*
Move in a straight line by lifting leg L1, R2, L3. Then move lifte legs forward, lower them, lift R1, L2, R3  and move the 1st set of legs backward. Then opposite side.
*/

PodMovementStep StraightMovement[] = {
  { // lift L1, R2, L3
    lmLiftLeg2, lmWait,
    lmWait,lmLiftLeg2,
    lmLiftLeg2,lmWait,
  },
  { // L1, R2, L3: forward lifted
    // R1, L2, R3: backward ground
    lmForward, lmBackward,
    lmBackward,lmForward,
    lmForward,lmBackward,
  },
  { // lower L1, R2, L3
    lmLowerLeg2, lmWait,
    lmWait,lmLowerLeg2,
    lmLowerLeg2,lmWait,
  },
  { // lift R1, L2, R3
    lmWait, lmLiftLeg2,
    lmLiftLeg2, lmWait,
    lmWait, lmLiftLeg2,
  },
  { // L1, R2, L3: backward ground
    // R1, L2, R3: forward air
    lmBackward, lmForward,
    lmForward,lmBackward,
    lmBackward,lmForward,
  }
};
#endif

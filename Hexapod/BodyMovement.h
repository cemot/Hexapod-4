/*
* This class calculates the endpoints of the body where the legs are attached for a given roll and pitch movement.
*/

#ifndef BODYMOVEMENT_H
#define BODYMOVEMENT_H

#include <arduino.h>
#include <math.h>
#include "Geometry.h";
#include "InverseKinematics.h";
#include "ServoControllerBoard.h";

int group1Pulses[] = {1000, 1250, 1500, 1250};
int legPulsesDirection[] = { -1, -1, -1, 1, 1, 1};
//const int PULSE_BASE = 1600;
const int PULSE_RADIUS = 500;

class BodyMovementCalc
{
  public:
    //    (Stream& serial, Stream& debugStream):
    //     _stream(serial), _debugStream(debugStream) // Need to initialise
    BodyMovementCalc(ServoControllerBoard & servoControllerBoard)
      : _servoControllerBoard(servoControllerBoard)
    {};

    // move all legs to initial flat position
    void Lift(int z)
    {   
        for (int leg = 1; leg <= 6; leg++) {
          for(int legSegment = 1; legSegment <= 3; legSegment++){
              int servoId = (leg - 1) * 3 + legSegment;
              int legDirection = legPulsesDirection[leg - 1];
              int pulse = 0;
              int deltaPulse = z * 400;
              
              if(legSegment == 1 ) // coxa hor.
              {
                continue; // skip leg horizontal rotation
                //pulse = 1000;
              }
              else if (legSegment == 2) // femur
              {
                //pulse = PULSE_BASE + legDirection * PULSE_RADIUS;
                pulse = INITIAL_POSITION + legDirection * deltaPulse;
              }
              else if (legSegment == 3) // tibia
              {
                pulse = INITIAL_POSITION + -1 * legDirection * deltaPulse * 1.5;
              }

              _servoControllerBoard.SetServoPosition(servoId, pulse);
        };
      };
      
      _servoControllerBoard.MoveAll(500);
    };

    //TODO: expose method to calculate the leg angles for a given body movement vector and timestep
    void Move()
    {
      // determine walking pattern
      // determine number of steps
      int stepsize = 3;
      for (int i = 0; i < stepsize; i++) {
        // determine required leg position P for step i

        // determine body positions Q
        // for each leg...
        for (int servoId = 1; servoId <= NUMBER_OF_SERVOS; servoId++) {
          // determine leg position PQ = P - Q
          // determine limb angles using IK
          // determine servo pulse
          // update servo position
          int servoPosition = group1Pulses[i]; // to determine
          _servoControllerBoard.SetServoPosition(servoId, servoPosition);
          // end for each leg ....
        }
        
        // execute servo controller board cmd
        int steptime = 500;
        _servoControllerBoard.MoveAll(steptime);
      };
    };

    /*
        // calculates the relative leg endpoints
        endpoints* CalculateRelativeLegPositions() {};

        // calculate the leg positions for this timestep
        void CalculateStepSize(endpoints endpoints) {};

        void CalculateLegAnglesForTimeStep() {};
    */

  private:
    //endpoints* _endpoints = new endpoints(P1, P2, P3, P4, P5, P6);
    InverseKinematicsLimb* _inverseKinematicsLimb = new InverseKinematicsLimb(15, 55, 90);
    ServoControllerBoard _servoControllerBoard;
    

    // calculate leg angles alpha, beta, gamma using IK
    // T1 to T6
    // angle leg 1
    //limbAngles* l1 = inverseKinematicsLimb->CalculateAngles(T->p1);
    // also calculate all other legs 2 to 6

    // send leg angles to MovementController


    endpoints* CalculateQ(endpoints* pEndpoints, double rollAngle, double pitchAngle)
    {
      double sinrho = sin(pitchAngle);
      double coseps = cos(rollAngle);
      double sineps = sin(rollAngle);

      endpoints* q = new endpoints(
        this->CalculateQ(pEndpoints->p1, sinrho, coseps, sineps),
        this->CalculateQ(pEndpoints->p2, sinrho, coseps, sineps),
        this->CalculateQ(pEndpoints->p3, sinrho, coseps, sineps),
        this->CalculateQ(pEndpoints->p4, sinrho, coseps, sineps),
        this->CalculateQ(pEndpoints->p5, sinrho, coseps, sineps),
        this->CalculateQ(pEndpoints->p6, sinrho, coseps, sineps)
      );

      return q;
    }

    point* CalculateQ(point* pValue, double sinrho, double coseps, double sineps)
    {
      double x = pValue->x;
      double y = pValue->y * (1 - coseps);
      double z = pValue->x * -sinrho + pValue->y * sineps + pValue->z;

      point* q = new point((int)x, (int)y, (int)z);;
      return q;
    }
};
#endif


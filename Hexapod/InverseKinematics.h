#ifndef INVERSEKINEMATICS_H
#define INVERSEKINEMATICS_H

#include <math.h>;
#include "BodyMovement.h";

struct limbAngles
{
  limbAngles(double alpha, double beta, double gamma)
  {
    this->alpha = alpha;
    this->beta = beta;
    this->gamma = gamma;
  }

  double alpha;
  double beta;
  double gamma;
};

// see http://www.engineer-this.com/IK.shtml
class InverseKinematicsLimb
{
  public:
    InverseKinematicsLimb(double coxaValue, double femurValue, double tibiaValue)
    {
      this->coxa = coxaValue;
      this->femur = femurValue;
      this->tibia = tibiaValue;
    }

    limbAngles* CalculateAngles(point* positionVector)
    {
      double x = positionVector->x;
      double y = positionVector->y;
      double z = positionVector->z;

      double gamma = atan(x / y);
      double yProjected = y * cos(gamma);
      double L = sqrt(square(z) + square(yProjected - coxa));

      double alpha1 = acos(z / L);
      double alpha2 = acos((square(tibia) - square(femur) - square(L)) / (-2 * femur * L));

      double alpha = alpha1 + alpha2;
      double beta = acos((square(L)-square(tibia) - square(femur))/(-2 * tibia * femur));;

      limbAngles* angles = new limbAngles(alpha, beta, gamma);
      return angles;
    }

  private:
    double coxa;
    double femur;
    double tibia;
};
#endif

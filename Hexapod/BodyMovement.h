#include <arduino.h>
#include <math.h>

int zBody = 40;

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

point* P1 = new point(-56, 31, 40);
point* P2 = new point(0, 42, 40);
point* P3 = new point(56, 42, 40);
point* P4 = new point(-56, -31, 40);
point* P5 = new point(0, -42, 40);
point* P6 = new point(56, -42, 40);

endpoints* pEndpoints = new endpoints(P1, P2, P3, P4, P5, P6);

class BodyMovementCalc
{
  public:
    endpoints* CalculateQ(endpoints* pEndpoints, double epsilon, double rho)
    {
      double sinrho = sin(rho);
      double coseps = cos(epsilon);
      double sineps = sin(epsilon);

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

  private:
    point* CalculateQ(point* pValue, double sinrho, double coseps, double sineps)
    {
      double x = pValue->x;
      double y = pValue->y * (1 - coseps);
      double z = pValue->x * -sinrho + pValue->y * sineps + pValue->z;

      point* q = new point((int)x, (int)y, (int)z);;
      return q;
    }
};


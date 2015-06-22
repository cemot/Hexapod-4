/*

Movement steps are defined as an array of legmovements, foreach joint (servo).
Since each leg has 3 joints (servo's) and the hexapod has 6 legs it needs 18 servo instructions per step.
*/

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




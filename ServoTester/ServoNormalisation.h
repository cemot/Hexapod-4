#ifndef SERVONORMALISATION_H
#define SERVONORMALISATION_H

// defines for each servo:
// - the neutral position
// - the direction
// - the pulse range

struct ServoDefinition
{
  ServoDefinition(int neutral, int min, int max) {
    this->neutralPulse = neutral;
    this->minPulse = min;
    this->maxPulse = max;
  };

  // pulse in the neutral position
  int neutralPulse;
  //int neutralAngle; // degrees

  // pulse at the minumum angle
  int minPulse;
  //int minAngle; // degrees

  // pulse at the maximum angle
  int maxPulse;
  //int maxAngle; // degrees
};

ServoDefinition definitions[] = { *new ServoDefinition(500, 1000, 1500), // leg 1 limb 1
                                  *new ServoDefinition(500, 1000, 1500),
                                  *new ServoDefinition(500, 1000, 1500),
                                  *new ServoDefinition(500, 1000, 1500),// leg 2 limb 1
                                  *new ServoDefinition(500, 1000, 1500),
                                  *new ServoDefinition(500, 1000, 1500),
                                  *new ServoDefinition(500, 1000, 1500),// leg 3 limb 1
                                  *new ServoDefinition(500, 1000, 1500),
                                  *new ServoDefinition(500, 1000, 1500),
                                  *new ServoDefinition(1500, 1000, 500),// leg 4 limb 1
                                  *new ServoDefinition(1500, 1000, 500),
                                  *new ServoDefinition(1500, 1000, 500),
                                  *new ServoDefinition(1500, 1000, 500),// leg 5 limb 1
                                  *new ServoDefinition(1500, 1000, 500),
                                  *new ServoDefinition(1500, 1000, 500),
                                  *new ServoDefinition(1500, 1000, 500),// leg 6 limb 1
                                  *new ServoDefinition(1500, 1000, 500),
                                  *new ServoDefinition(1500, 1000, 500),
                                };

// contains all 18 servo definitions
class ServoNormalisation
{
  public:
  private:

};

#endif

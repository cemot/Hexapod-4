/*
 * Class that handles the movement vector and updates the Servo's
 */

#ifndef MOVEMENTCONTROLLER_H
#define MOVEMENTCONTROLLER_H

class MovementController
{
    MovementController() {};

    ~MovementController() {};
};

/*
 * Class defines an actual movement state for the hexapod body
 */
class MovementVector
{
  public:

    MovementVector()
    {
    }

    ~MovementVector()
    {
    }

    double GetRoll()
    {
      return this->roll;
    }

    double GetPitch()
    {
      return this->pitch;
    }

    void SetHeave(double z)
    {
      this->heave += z;
    }
    
    void SetSurge(double f)
    {
      this->surge += f;
    }

    void SetYaw(double y)
    {
      this->yaw += y;
    }

    void SetPitch(double f)
    {
      this->pitch += f;
    }

    void SetRoll(double y)
    {
      this->roll += y;
    }

    void SetStop()
    {
      this->surge = 0;
      this->sway = 0;
      this->heave = 0;
      this->roll = 0;
      this->pitch = 0;
      this->yaw = 0;
    }

    String ToString()
    {
      String s = "#MV:S:";
      s += String(this->surge, 1);
      s += ";Y:";
      s += String(this->sway, 1);
      s += ";H:";
      s += String(this->heave, 1);
      s += ";r:";
      s += String(this->roll, 1);
      s += ";p:";
      s += String(this->pitch, 1);
      s += ";y:";
      s += String(this->yaw, 1);
      s += ";";
      return s;
    }

    // reads values from input string
    void Parse(String value)
    {
      if (!value.startsWith("#MV:S:"))
      {
        return;
      }

      int readPosition = 4;
      int stringLength = value.length();
      while (readPosition >= 0 && readPosition < stringLength)
      {
        // find field
        char cmd = value.charAt(readPosition);

        // find : semicolon
        int dataStartIndex = value.indexOf(":", readPosition);

        // read double value between : and #
        int fieldTerminatorPosition = value.indexOf(";", readPosition);
        String v = value.substring(dataStartIndex + 1, fieldTerminatorPosition - 1);

        // write info field
        double f = v.toFloat();
        switch (cmd) {
          case 'S':
            this->surge = f;
            break;
          case 'Y':
            this->sway = f;
            break;
          case 'H':
            this->heave = f;
            break;
          case 'r':
            this->roll = f;
            break;
          case 'p':
            this->pitch = f;
            break;
          case 'y':
            this->yaw = f;
            break;
          default:
            break;
        }

        // truncate remaining string
        readPosition = fieldTerminatorPosition + 1;
      }
    }

  private:
    double surge;
    double sway;
    double heave;
    double roll;
    double pitch;
    double yaw;

};
#endif

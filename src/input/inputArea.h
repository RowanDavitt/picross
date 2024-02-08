
#ifndef INPUTAREA
#define INPUTAREA
#include "raylib.h"

class inputArea {
public:
  virtual bool inArea(Vector2 location) = 0;
  virtual int pressInputDown(int button, Vector2 mouse_pos, int global_hold) = 0;
  virtual void pressInputUp(int button, Vector2 mouse_pos) = 0;
};
#endif
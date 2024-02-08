
#ifndef LOADBUTTON
#define LOADBUTTON
#include "helper/ColorConsts.h"
#include "helper/helper.h"
#include "helper/outlinedDraw.h"
#include "inputArea.h"
#include "inputHandler.h"

#include <string>
#include <vector>
class textButton : public inputArea {
  int BUTTON_MARGIN_RATIO = 5;
  Vector2 position;
  Vector2 size;
  int text_height;
  float margin;
  Vector2 text_off;
  ElemCC::ColorVal buttonColour;

public:
  std::string fileName;
  int done = 0;
  textButton(Vector2 location, Vector2 dimensions, std::string displayText, ElemCC::ColorVal b_colour);
  void resize(Vector2 location, Vector2 dimensions);
  void draw();

  bool inArea(Vector2 location);
  int pressInputDown(int button, Vector2 mouse_pos, int global_hold);
  void pressInputUp(int button, Vector2 mouse_pos);
};

#endif
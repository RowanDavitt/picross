
#ifndef LOADBUTTON
#define LOADBUTTON
#include "helper/ColorConsts.h"
#include "helper/helper.h"
#include "helper/outlinedDraw.h"
#include "input/inputArea.h"

#include <string>
#include <vector>
class fileButton {
  int BUTTON_MARGIN_RATIO = 5;
  Vector2 position;
  Vector2 size;
  int text_height;
  float margin;
  Vector2 text_off;

public:
  std::string fileName;
  int done = 0;
  fileButton(Vector2 location, Vector2 dimensions, std::string displayText);

  bool inArea(Vector2 location);
  void resize(Vector2 location, Vector2 dimensions);
  int pressInputDown(int button, Vector2 mouse_pos);
  void draw();
};

#endif
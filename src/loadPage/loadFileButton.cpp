
#include "loadFileButton.h"
#include "input/fileInput.h"
#include "raylib.h"

fileButton::fileButton(Vector2 location, Vector2 dimensions, std::string displayText) {
  fileName = displayText;
  done = 0;
  resize(location, dimensions);
}

void fileButton::resize(Vector2 location, Vector2 dimensions) {
  position = location;
  size = dimensions;
  margin = size.y / BUTTON_MARGIN_RATIO;
  text_height = size.y - margin * 2;
  text_off = Vector2{margin, margin};
}

bool fileButton::inArea(Vector2 location) {
  return (location.x > position.x &&
          location.y > position.y &&
          location.x < (position.x + size.x) &&
          location.y < (position.y + size.y));
}
int fileButton::pressInputDown(int button, Vector2 mouse_pos) {
  if (inArea(mouse_pos)) {
    if (button == MOUSE_BUTTON_LEFT) {
      done = 1;
    }
  }
  return -1;
}

void fileButton::draw() {
  drawOutLineBox(position, size, 5, ElemCC::ColorVal::GRID_LINES);
  DrawSuperText(removeplzExt(fileName).c_str(), addVec(position, text_off), 0, text_height, 3, ElemCC::LABEL_TEXT);
}
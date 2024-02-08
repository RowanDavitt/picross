
#include "textButton.h"
#include "fileInput.h"
#include "raylib.h"

textButton::textButton(Vector2 location, Vector2 dimensions, std::string displayText, ElemCC::ColorVal b_colour) {
  fileName = displayText;
  done = 0;
  resize(location, dimensions);
  buttonColour = b_colour;
}

void textButton::resize(Vector2 location, Vector2 dimensions) {
  position = location;
  size = dimensions;
  margin = size.y / BUTTON_MARGIN_RATIO;
  text_height = size.y - margin * 2;
  text_off = Vector2{margin, margin};
}

bool textButton::inArea(Vector2 location) {
  return (location.x > position.x &&
          location.y > position.y &&
          location.x < (position.x + size.x) &&
          location.y < (position.y + size.y));
}
int textButton::pressInputDown(int button, Vector2 mouse_pos, int global_hold) {
  if (inArea(mouse_pos)) {
    if (button == MOUSE_BUTTON_LEFT) {
      done = 1;
    }
  }
  return -1;
}

void textButton::draw() {
  drawOutLineBox(position, size, 5, buttonColour);
  DrawSuperText(removeplzExt(fileName).c_str(), addVec(position, text_off), 0, text_height, 3, ElemCC::LABEL_TEXT);
}
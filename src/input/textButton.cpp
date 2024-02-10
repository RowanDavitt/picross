
#include "textButton.h"
#include "fileInput.h"
#include "raylib.h"

textButton::textButton(Vector2 location, Vector2 dimensions, std::string displayText, ElemCC::ColorVal b_colour, ElemCC::ColorVal t_colour) {
  buttonText = displayText;
  done = 0;
  resize(location, dimensions);
  buttonColour = b_colour;
  textColour = t_colour;
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
  if (global_hold == -1) {
    return button;
  }
  return -1;
}

void textButton::pressInputUp(int button, Vector2 mouse_pos) {
  if (button == MOUSE_BUTTON_LEFT && inArea(mouse_pos)) {
    done = 1;
  }
}

void textButton::draw() {
  drawBoxWithText(buttonText.c_str(), size, position, 5, 3, buttonColour, textColour);
}
#include "outlinedDraw.h"
#include "helper.h"
#include <cmath>

// Draws a line with outline
void drawOutLineLine2D(Vector2 start, Vector2 end, float margin, float thickness, ElemCC::ColorVal col) {
  DrawLineEx(start, end, thickness + (2 * margin), ElemCC::COLOUR_LOOKUP[col]);
  drawSubLine2D(start, end, margin, thickness, col);
}

// draws the inner line of an outlined line
void drawSubLine2D(Vector2 start, Vector2 end, float margin, float thickness, ElemCC::ColorVal col) {
  double angle = vecAngle(start, end);
  Vector2 angle_margins = {
      (float)(margin * cos(angle)),
      (float)(margin * sin(angle))};

  DrawLineEx(addVec(start, angle_margins), subVec(end, angle_margins), thickness, ElemCC::SUB_LOOKUP[col]);
}

void drawGridLines2D(Vector2 origin, Vector2 grid_size, Vector2 cell_num, Vector2 spacing, float thickness, Color col) {
  Vector2 start = origin;
  Vector2 end = origin;
  start.y -= (thickness / 2);
  end.y += grid_size.y + (thickness / 2);
  for (int i = 0; i < cell_num.x; i++) {
    DrawLineEx(start, end, thickness, col);

    start.x += spacing.x;
    end.x += spacing.x;
  }
  start.x = grid_size.x + origin.x;
  end.x = grid_size.x + origin.x;
  DrawLineEx(start, end, thickness, col);

  start = origin;
  end = origin;
  start.x -= (thickness / 2);
  end.x += grid_size.x + (thickness / 2);
  for (int i = 0; i < cell_num.y; i++) {
    DrawLineEx(start, end, thickness, col);

    start.y += spacing.y;
    end.y += spacing.y;
  }
  start.y = grid_size.y + origin.y;
  end.y = grid_size.y + origin.y;
  DrawLineEx(start, end, thickness, col);
}

void drawOutlineGridLines2D(Vector2 origin, Vector2 grid_size, Vector2 cell_num, float margin, float thickness, ElemCC::ColorVal col) {
  Vector2 spacing = divVec(grid_size, cell_num);
  drawGridLines2D(origin, grid_size, cell_num, spacing, thickness, ElemCC::COLOUR_LOOKUP[col]);
  drawGridLines2D(origin, grid_size, cell_num, spacing, thickness - (2 * margin), ElemCC::SUB_LOOKUP[col]);
}

void DrawSuperText(const char *text, Vector2 loc, int offset, int char_height, int outlineThickness, ElemCC::ColorVal text_colour) {
  char_height -= outlineThickness * 2;
  loc.x += offset + outlineThickness;
  loc.y += outlineThickness;
  for (int i = -outlineThickness; i <= outlineThickness; i++)
    for (int j = -outlineThickness; j <= outlineThickness; j++) {
      DrawText(text, loc.x + i, loc.y + j, char_height, ElemCC::COLOUR_LOOKUP[text_colour]);
    }

  DrawText(text, loc.x, loc.y, char_height, ElemCC::SUB_LOOKUP[text_colour]);
}

void drawOutLineBox(Vector2 location, Vector2 dimensions, float border_thickness, ElemCC::ColorVal col) {
  Rectangle rect{location.x + (border_thickness / 2), location.y + (border_thickness / 2), dimensions.x - border_thickness, dimensions.y - border_thickness};
  DrawRectangleV(addVec(location, border_thickness), addVec(dimensions, -(2 * border_thickness)), ElemCC::SUB_LOOKUP[col]);
  DrawRectangleLinesEx(rect, border_thickness, ElemCC::COLOUR_LOOKUP[col]);
}

// pos is top left, text will be centered
void drawBoxWithText(const char *msg,
                     Vector2 size,
                     Vector2 pos,
                     float box_border_thick,
                     float text_border_thick,
                     ElemCC::ColorVal box_col,
                     ElemCC::ColorVal text_col) {

  Vector2 textPos = addVec(pos, divVec(size, 2));
  ;
  drawOutLineBox(pos, size, box_border_thick, box_col);
  float textHeight = getTextsizeInBound(msg, size, 0.75).y;
  textPos.x -= MeasureText(msg, textHeight - (2 * text_border_thick)) / 2;
  textPos.y -= textHeight / 2;
  DrawSuperText(msg, textPos, 0, textHeight, text_border_thick, text_col);
}

// pos is top left, text will be centered
void drawTextInBound(const char *msg,
                     Vector2 size,
                     Vector2 pos,
                     float text_border_thick, float margin,
                     ElemCC::ColorVal text_col) {

  Vector2 textPos = addVec(pos, divVec(size, 2));
  float textHeight = getTextsizeInBound(msg, size, margin).y;
  textPos.x -= MeasureText(msg, textHeight - (2 * text_border_thick)) / 2;
  textPos.y -= textHeight / 2;
  DrawSuperText(msg, textPos, 0, textHeight, text_border_thick, text_col);
}
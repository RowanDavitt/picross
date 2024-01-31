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
  for (int i = 0; i <= cell_num.x; i++) {
    DrawLineEx(start, end, thickness, col);

    start.x += spacing.x;
    end.x += spacing.x;
  }

  start = origin;
  end = origin;
  spacing = divVec(grid_size, cell_num);
  start.x -= (thickness / 2);
  end.x += grid_size.x + (thickness / 2);
  for (int i = 0; i <= cell_num.y; i++) {
    DrawLineEx(start, end, thickness, col);

    start.y += spacing.y;
    end.y += spacing.y;
  }
}

void drawOutlineGridLines2D(Vector2 origin, Vector2 grid_size, Vector2 cell_num, float margin, float thickness, ElemCC::ColorVal col) {
  Vector2 spacing = divVec(grid_size, cell_num);
  drawGridLines2D(origin, grid_size, cell_num, spacing, thickness, ElemCC::COLOUR_LOOKUP[col]);
  drawGridLines2D(origin, grid_size, cell_num, spacing, thickness - (2 * margin), ElemCC::SUB_LOOKUP[col]);
}

void DrawSuperText(const char *text, Vector2 loc, int offset, int char_height, int outlineThickness, ElemCC::ColorVal text_colour) {
  loc.x += offset;
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
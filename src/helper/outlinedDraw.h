#ifndef OUT_DRAW
#define OUT_DRAW
#include "ColorConsts.h"
#include "raylib.h"

void drawOutLineLine2D(Vector2 start, Vector2 end, float margin, float thickness, ElemCC::ColorVal col);
void drawSubLine2D(Vector2 start, Vector2 end, float margin, float thickness, ElemCC::ColorVal col);
void drawGridLines2D(Vector2 origin, Vector2 grid_size, Vector2 cell_num, Vector2 spacing, float thickness, Color col);
void drawOutlineGridLines2D(Vector2 origin, Vector2 grid_size, Vector2 cell_num, float margin, float thickness, ElemCC::ColorVal col);

void DrawSuperText(const char *text, Vector2 loc, int offset, int char_height, int outlineThickness, ElemCC::ColorVal text_colour);
void drawOutLineBox(Vector2 location, Vector2 dimensions, float border_thickness, ElemCC::ColorVal col);
void drawBoxWithText(const char *msg, Vector2 size, Vector2 pos, float box_border_thick, float text_border_thick, ElemCC::ColorVal box_col, ElemCC::ColorVal text_col);
#endif
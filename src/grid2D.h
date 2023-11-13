#include "ColorConsts.h"
#include "cell2D.h"
#include "raylib.h"
#include <vector>

#ifndef GRID_2D
#define GRID_2D

class grid2D {
private:
  static const int THICK_RATIO = 14;
  static const int LINE_MARG_RATIO = 2;

public:
  float line_thickness;
  float base_thick;
  float line_marg;
  Vector2 origin;
  Vector2 grid_size;
  Vector2 cell_num;
  Vector2 spacing;
  ElemCC::ColorVal colour = ElemCC::ColorVal::GRID_LINES;
  std::vector<std::vector<cell2D>> cells;

  grid2D(Vector2 loc, Vector2 grid_size, Vector2 num_cells);
  grid2D() {}

  Vector2 getCellGridPos(Vector2 grid_pos);
  cell2D *getCell(Vector2 screen_pos);
  void drawGrid2D();
  bool onBoard(Vector2 screen_pos);
  void unhighlight();
  void calculateGridSize(Vector2 loc, Vector2 grid_size);
  void recalculateCellSize();
};
#endif
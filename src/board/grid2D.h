#include "cell2D.h"
#include "helper/ColorConsts.h"
#include "input/inputArea.h"
#include "input/inputHandler.h"
#include "raylib.h"
#include <vector>

#ifndef GRID_2D
#define GRID_2D

class grid2D : public inputArea {
private:
  static const int THICK_RATIO = 14;
  static const int LINE_MARG_RATIO = 2;
  int board_hold = -1;
  bool clear_mode = 0;
  Vector2 start_cell_coord;

public:
  float line_thickness;
  float base_thick;
  float line_marg;
  Vector2 origin = {0, 0};
  Vector2 grid_size = {0, 0};
  Vector2 cell_num = {0, 0};
  Vector2 spacing = {0, 0};
  ElemCC::ColorVal colour = ElemCC::ColorVal::GRID_LINES;
  std::vector<std::vector<cell2D>> cells;

  grid2D(Vector2 loc, Vector2 spacing, Vector2 grid_size, Vector2 num_cells);
  grid2D() {}

  Vector2 getCellGridPos(Vector2 grid_pos);
  cell2D *getCell(Vector2 screen_pos);
  void drawGrid2D();
  void unhighlight();
  void calculateGridSize(Vector2 loc, Vector2 spacing, Vector2 grid_size, Vector2 num_cells);
  void recalculateCellSize();
  void paintHighlighted(bool clear_mode, ElemCC::ColorVal painting_colour);
  void buildGrid();

  bool inArea(Vector2 location);
  int pressInputDown(int button, Vector2 mouse_pos, int global_hold);
  void pressInputUp(int button);
};
#endif
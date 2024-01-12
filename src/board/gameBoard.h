#ifndef GAME_BOARD
#define GAME_BOARD
#include "grid2D.h"
#include "helper/ColorConsts.h"
#include "input/inputArea.h"
#include "labelSet.h"
#include "raylib.h"

class gameBoard : public inputArea {
public:
  int board_hold = -1;
  bool clear_mode;
  Vector2 start_cell_coord;

  Vector2 spacing;
  Vector2 origin;
  Vector2 grid_size;
  Vector2 board_size;
  Vector2 grid_origin;
  Vector2 num_cells;
  grid2D grid;
  labelSet labels;
  constexpr static float LABEL_HEIGHT_RATIO = 1.25; // to calculate label height relative to grid size
  const static int GRID_MARGIN_RATIO = 5;           // ratio to calculate distance from edge of screen to grid
  int label_height;
  int grid_margin;

  std::vector<std::vector<bool>> puzzle;
  gameBoard(std::vector<std::vector<bool>> *input_puzzle);
  gameBoard() {}
  void calculateGameBoard();
  void recalculateElements();
  void drawGameBoard();
  std::vector<std::vector<bool>> getBoardState();
  bool checkWin();
  void boardFrame();

  bool inArea(Vector2 loc) override;
  int pressInputDown(int button, Vector2 mouse_pos, int global_hold) override;
  void pressInputUp(int button) override;
};

#endif
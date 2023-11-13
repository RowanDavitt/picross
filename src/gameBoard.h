#include "ColorConsts.h"
#include "grid2D.h"
#include "labelSet.h"
#include "raylib.h"

#ifndef GAME_BOARD
#define GAME_BOARD

class gameBoard {
public:
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
};

#endif
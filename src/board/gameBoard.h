#ifndef GAME_BOARD
#define GAME_BOARD
#include "grid2D.h"
#include "helper/ColorConsts.h"
#include "input/inputHandler.h"
#include "labelSet.h"
#include "raylib.h"

class gameBoard {

public:
  Vector2 spacing;
  Vector2 origin;
  Vector2 grid_size;
  Vector2 board_size;
  Vector2 grid_origin;
  Vector2 num_cells;
  grid2D *grid = new grid2D();
  labelSet labels;
  constexpr static float LABEL_HEIGHT_RATIO = 5; // to calculate label height relative to grid size
  const static int GRID_MARGIN_RATIO = 15;       // ratio to calculate distance from edge of screen to grid
  int label_height;
  int grid_margin;
  std::vector<std::vector<bool>> *puzzle;
  inputHandler inputter = inputHandler();

  gameBoard(std::vector<std::vector<bool>> *input_puzzle);
  gameBoard() {}
  void calculateGameBoard();
  void recalculateElements();
  void drawGameBoard();
  std::vector<std::vector<bool>> getBoardState();
  bool checkWin();
  void boardFrame();
};

#endif
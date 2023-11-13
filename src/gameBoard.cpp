#include "gameBoard.h"
#include "helper.h"

// The board the game is played from a usisng a 2D vector decribing the winning state
gameBoard::gameBoard(std::vector<std::vector<bool>> *input_puzzle) {
  puzzle = *input_puzzle;
  calculateGameBoard();

  grid = grid2D(origin, board_size, num_cells);
  labels = labelSet(origin, grid.spacing, num_cells, label_height, grid.line_thickness, input_puzzle);
}

// Recalculate the position and dimesnsions of the baords contents, adjust for a change to the board
// Intended for when the window is resized
void gameBoard::recalculateElements() {
  grid.calculateGridSize(origin, board_size);
  grid.recalculateCellSize();

  labels.calculateSize(origin, grid.spacing, label_height, grid.line_thickness);
}

// calculate the position and dimensions and location of the board
// Intended for when the board is initialized or the window is resized
void gameBoard::calculateGameBoard() {
  grid_margin = min(GetScreenHeight(), GetScreenWidth()) / GRID_MARGIN_RATIO;
  label_height = grid_margin / LABEL_HEIGHT_RATIO;
  float grid_base = min(GetScreenWidth(), GetScreenHeight());

  origin = {((GetScreenWidth() - grid_base) / 2 + grid_margin), ((GetScreenHeight() - grid_base) / 2 + grid_margin)};

  board_size = {(GetScreenWidth() - (2 * origin.x)), (GetScreenHeight() - (2 * origin.y))};
  origin = addVec(origin, label_height / 2);

  num_cells = {(float)(puzzle)[0].size(), (float)(puzzle).size()};
}

// Draw the board and all it's contents (includes labels)
void gameBoard::drawGameBoard() {
  labels.drawXLabel();
  labels.drawYLabel();
  grid.drawGrid2D();
}

// create a 2d boolean vector desribing the state of the current board
std::vector<std::vector<bool>> gameBoard::getBoardState() {
  std::vector<std::vector<bool>> b_state;
  for (unsigned int y = 0; y < grid.cells.size(); y++) {
    b_state.push_back(std::vector<bool>());

    for (unsigned int x = 0; x < grid.cells[y].size(); x++) {
      b_state[y].push_back(grid.cells[y][x].painted == ElemCC::ColorVal::CELL_FILL);
    }
  }
  return b_state;
}

// Checks if the baord is in the winning state
bool gameBoard::checkWin() {
  std::vector<std::vector<bool>> b_state = getBoardState();
  bool win = true;
  for (unsigned int y = 0; y < b_state.size(); y++) {
    for (unsigned int x = 0; x < b_state[y].size(); x++) {
      win = win && (b_state[y][x] == puzzle[y][x]);
    }
  }
  return win;
}
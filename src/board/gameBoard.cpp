#include "gameBoard.h"
#include "helper/helper.h"

// The board the game is played from a usisng a 2D vector decribing the winning state
gameBoard::gameBoard(std::vector<std::vector<bool>> *input_puzzle) {
  puzzle = input_puzzle;
  calculateGameBoard();

  grid = new grid2D(origin, spacing, board_size, num_cells);
  labels = labelSet(origin, spacing, num_cells, label_height, grid->line_thickness, input_puzzle);
  inputter.addRegion(grid);
}

// Recalculate the position and dimesnsions of the baords contents, adjust for a change to the board
// Intended for when the window is resized
void gameBoard::recalculateElements() {
  calculateGameBoard();
  grid->calculateGridSize(origin, spacing, board_size, num_cells);
  grid->recalculateCellSize();

  labels.calculateSize(origin, spacing, num_cells, label_height, grid->line_thickness);
}

// calculate the position and dimensions and location of the board
// Intended for when the board is initialized or the window is resized
void gameBoard::calculateGameBoard() {
  float grid_base = min(GetScreenWidth(), GetScreenHeight());
  grid_margin = grid_base / GRID_MARGIN_RATIO;
  label_height = grid_base / LABEL_HEIGHT_RATIO;

  if (puzzle->empty()) {
    num_cells = {0, 0};
  } else {
    num_cells = {(float)(*puzzle)[0].size(), (float)(*puzzle).size()};
  }

  origin = {(((GetScreenWidth() - grid_base) / 2) + grid_margin + label_height),
            (((GetScreenHeight() - grid_base) / 2) + grid_margin + label_height)};

  board_size = {(float)(GetScreenWidth() - ((2 * grid_margin) + label_height)),
                (float)(GetScreenHeight() - ((2 * grid_margin) + label_height))};

  spacing = doubleMinMag(divVec(board_size, num_cells));
  board_size = scaleVec(num_cells, spacing);
  origin = {(((GetScreenWidth() - board_size.x) + label_height) / 2),
            (((GetScreenHeight() - board_size.y) + label_height) / 2)};
}

// Draw the board and all it's contents (includes labels)
void gameBoard::drawGameBoard() {
  labels.drawXLabel();
  labels.drawYLabel();
  grid->drawGrid2D();
}

// create a 2d boolean vector desribing the state of the current board
std::vector<std::vector<bool>> gameBoard::getBoardState() {
  std::vector<std::vector<bool>> b_state;
  for (unsigned int y = 0; y < grid->cells.size(); y++) {
    b_state.push_back(std::vector<bool>());

    for (unsigned int x = 0; x < grid->cells[y].size(); x++) {
      b_state[y].push_back(grid->cells[y][x].painted == ElemCC::ColorVal::CELL_FILL);
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
      win = win && (b_state[y][x] == (*puzzle)[y][x]);
    }
  }
  return win;
}

void gameBoard::boardFrame() {
  if (IsWindowResized()) {
    recalculateElements();
  }
  inputter.checkClick();

  if (checkWin()) {
    DrawText("win", 10, 100, 20, RAYWHITE);
  }
  drawGameBoard();
}

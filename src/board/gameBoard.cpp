#include "gameBoard.h"
#include "helper/helper.h"

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

void gameBoard::boardFrame() {

  if (IsWindowResized()) {
    calculateGameBoard();
    recalculateElements();
  }

  if (checkWin()) {
    DrawText("win", 10, 100, 20, RAYWHITE);
  }
}

bool gameBoard::inArea(Vector2 loc) {
  return grid.inGrid(loc);
}

int gameBoard::pressInputDown(int button, Vector2 mouse_pos, int global_hold) {
  if (!grid.inGrid(mouse_pos)) {
    return 0;
  }
  Vector2 curr_coord = grid.getCellGridPos(mouse_pos);
  cell2D curr_cell = grid.cells[curr_coord.y][curr_coord.x];
  if (global_hold != -1 && board_hold == -1) {
    return 0;
  }
  if (board_hold == -1) {
    clear_mode = (curr_cell.painted == ElemCC::inputButtonColor[button]);
    start_cell_coord = curr_coord;
    board_hold = button;
  }

  grid.unhighlight();
  Vector2 delta_coord = keepMaxMag(subVec(curr_coord, start_cell_coord));
  Vector2 increment = signVec(delta_coord);
  Vector2 cap = addVec(addVec(start_cell_coord, delta_coord), increment);
  Vector2 curr = start_cell_coord;

  do {
    grid.cells[curr.y][curr.x].highlight = true;
    curr = addVec(curr, increment);
  } while ((!vecEquals(curr, cap)));

  return board_hold;
}

void gameBoard::pressInputUp(int button) {
  if (board_hold == button) {
    grid.paintHighlighted(clear_mode, ElemCC::inputButtonColor[board_hold]);
    board_hold = -1;
    grid.unhighlight();
  }
}

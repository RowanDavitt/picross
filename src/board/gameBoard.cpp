#include "gameBoard.h"
#include "helper/helper.h"
#include "helper/outlinedDraw.h"

// The board the game is played from a usisng a 2D vector decribing the winning state
gameBoard::gameBoard(std::vector<std::vector<bool>> *input_puzzle) {
  puzzle = input_puzzle;
  calculateGameBoard();
  backButtonSize = setBothVec((float)label_height * 0.75);

  grid = new grid2D(origin, spacing, board_size, num_cells);
  labels = labelSet(origin, spacing, num_cells, label_height, grid->line_thickness, input_puzzle);
  backButton = new textButton(addVec(origin, -label_height), backButtonSize, "Back", ElemCC::ColorVal::Back_BUTTON, ElemCC::ColorVal::LABEL_TEXT);
  inputter.addRegion(grid);
  inputter.addRegion(backButton);
}

// Recalculate the position and dimesnsions of the baords contents, adjust for a change to the board
// Intended for when the window is resized
void gameBoard::recalculateElements() {
  calculateGameBoard();
  grid->calculateGridSize(origin, spacing, board_size, num_cells);
  grid->recalculateCellSize();

  labels.calculateSize(origin, spacing, num_cells, label_height, grid->line_thickness);
  backButton->resize(addVec(origin, -label_height), backButtonSize);
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

  Vector2 screen_dim = {(float)GetScreenWidth(), (float)GetScreenHeight()};
  origin = addVec(divVec(addVec(screen_dim, -grid_base), 2), grid_margin + label_height);
  board_size = addVec(screen_dim, -((2 * grid_margin) + label_height));

  spacing = doubleMinMag(divVec(board_size, num_cells));
  board_size = scaleVec(num_cells, spacing);
  origin = divVec(addVec(subVec(screen_dim, board_size), label_height), 2);
  backButtonSize = setBothVec(((float)label_height) * 0.85);
}

// Draw the board and all it's contents (includes labels)
void gameBoard::drawGameBoard() {
  drawBackButton();
  labels.drawXLabel();
  labels.drawYLabel();
  grid->drawGrid2D();
  if (checkWin()) {
    if (!won) {
      inputter.clearAreas();
      inputter.addRegion(backButton);
      won = 1;
      blockRemaining();
    }
    displayWin();
  }
}

void gameBoard::drawBackButton() {
  backButton->draw();
}

void gameBoard::displayWin() {
  Vector2 screen_dim = {(float)GetScreenWidth(), (float)GetScreenHeight()};
  Vector2 size = scaleVec(screen_dim, 0.4);
  Vector2 pos = origin;
  pos.y -= label_height;
  size.y = label_height * 0.85;
  size.x = board_size.x;

  float thick = minVec(size) / 20;
  drawBoxWithText(WIN_MESSAGE, size, pos, thick, thick, ElemCC::ColorVal::WIN_BOX, ElemCC::ColorVal::LABEL_TEXT);
}

// create a 2d boolean vector desribing the state of the current board
std::vector<std::vector<bool>> gameBoard::getBoardState() {
  std::vector<std::vector<bool>> b_state;
  for (size_t y = 0; y < grid->cells.size(); y++) {
    b_state.push_back(std::vector<bool>());

    for (size_t x = 0; x < grid->cells[y].size(); x++) {
      b_state[y].push_back(grid->cells[y][x].painted == ElemCC::ColorVal::CELL_FILL);
    }
  }
  return b_state;
}

// Checks if the baord is in the winning state
bool gameBoard::checkWin() {
  std::vector<std::vector<bool>> b_state = getBoardState();
  bool win = true;
  for (size_t y = 0; y < b_state.size(); y++) {
    for (size_t x = 0; x < b_state[y].size(); x++) {
      win = win && (b_state[y][x] == (*puzzle)[y][x]);
    }
  }
  return win;
}

int gameBoard::boardFrame() {
  if (IsWindowResized()) {
    recalculateElements();
  }
  inputter.checkClick();
  if (backButton->done) {
    return EXIT_SUCCESS;
  }
  drawGameBoard();
  return EXIT_FAILURE;
}

void gameBoard::reset() {
  won = 0;
  backButton->done = 0;
  calculateGameBoard();
  backButtonSize = setBothVec((float)label_height * 0.75);

  grid = new grid2D(origin, spacing, board_size, num_cells);
  labels = labelSet(origin, spacing, num_cells, label_height, grid->line_thickness, puzzle);
  inputter.addRegion(grid);
  recalculateElements();
}

void gameBoard::blockRemaining() {
  for (size_t y = 0; y < grid->cells.size(); y++) {
    for (size_t x = 0; x < grid->cells[y].size(); x++) {
      if (grid->cells[y][x].painted == ElemCC::ColorVal::CELL_EMPTY) {
        grid->cells[y][x].painted = ElemCC::ColorVal::CELL_BLOCK;
      }
    }
  }
}

#include "inputHandler.h"
#include "board/cell2D.h"
#include "board/grid2D.h"
#include "helper/helper.h"

inputHandler::inputHandler(gameBoard *in_board) {
  board = in_board;
}

void inputHandler::checkClick(int button, ElemCC::ColorVal state) {
  Vector2 mouse_pos = GetMousePosition();
  bool on_screen = (*board).grid.onBoard(mouse_pos);
  bool is_release = IsMouseButtonReleased(button);

  if (on_screen) {
    bool is_down = IsMouseButtonDown(button);
    Vector2 curr_coord = (*board).grid.getCellGridPos(mouse_pos);
    cell2D curr_cell = (*board).grid.cells[curr_coord.y][curr_coord.x];

    if (is_down && !held) {
      clear_mode = (curr_cell.painted == state);
      painting_colour = state;
      start_cell_coord = curr_coord;
      held = true;
    }

    if (held) {
      (*board).grid.unhighlight();
      Vector2 delta_coord = keepMaxMag(subVec(curr_coord, start_cell_coord));
      Vector2 increment = signVec(delta_coord);
      Vector2 cap = addVec(addVec(start_cell_coord, delta_coord), increment);
      Vector2 curr = start_cell_coord;

      do {
        (*board).grid.cells[curr.y][curr.x].highlight = true;
        curr = addVec(curr, increment);
      } while ((!vecEquals(curr, cap)));
    }
  }

  if (held && (is_release || !on_screen)) {
    paintHighlighted();
    held = false;
    (*board).grid.unhighlight();
  }
}

void inputHandler::paintHighlighted() {
  for (unsigned int i = 0; i < (*board).grid.cells.size(); i++) {
    for (unsigned int j = 0; j < (*board).grid.cells[i].size(); j++) {
      if ((*board).grid.cells[i][j].highlight) {
        if (!clear_mode) {
          (*board).grid.cells[i][j].painted = painting_colour;
        } else {
          if ((*board).grid.cells[i][j].painted == painting_colour) {
            (*board).grid.cells[i][j].painted = ElemCC::ColorVal::CELL_EMPTY;
          }
        }
      }
    }
  }
}
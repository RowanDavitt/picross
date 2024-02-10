#include "grid2D.h"
#include "helper/helper.h"
#include "helper/outlinedDraw.h"
#include <string>

// A grid made up of a collection if cells
// Current implementation takes into account the size of the labels
grid2D::grid2D(Vector2 loc, Vector2 space, Vector2 board_size, Vector2 num_cells) {
  cell_num = num_cells;
  calculateGridSize(loc, space, board_size, num_cells);
}

// Calculate the dimensions and location of the grid
// Intended for when grid is initiazed or re-sized
void grid2D::calculateGridSize(Vector2 loc, Vector2 space, Vector2 board_size, Vector2 num_cells) {

  cell_num.x = num_cells.x;
  cell_num.y = num_cells.y;
  spacing = space;
  grid_size = scaleVec(cell_num, spacing);

  base_thick = minVec(spacing) / THICK_RATIO;
  line_marg = base_thick / LINE_MARG_RATIO;
  line_thickness = (base_thick + 2 * line_marg);
  origin = loc;
  if (cells.empty() || cells.size() != cell_num.y || cells[0].size() != cell_num.x) {
    buildGrid();
  }
}

// if the number of cells in the grid change this function can be called to clear the grid and remake it
void grid2D::buildGrid() {
  Vector2 curr = origin;
  for (size_t i = 0; i < cell_num.y; i++) {
    if (i >= cells.size()) {
      cells.emplace_back();
    }
    for (size_t j = 0; j < cell_num.x; j++) {
      if (j >= cells[i].size()) {
        cells[i].emplace_back(addVec(curr, line_thickness / 2), addVec(spacing, -line_thickness));
      } else {
        cells[i][j] = cell2D(addVec(curr, line_thickness / 2), addVec(spacing, -line_thickness));
      }
      curr.x += spacing.x;
    }
    curr.y += spacing.y;
    curr.x = origin.x;
  }
}

// adjusts the size of cells, intended for when grid size or location is adjusted
void grid2D::recalculateCellSize() {
  float line_thickness = (base_thick + 2 * line_marg);
  Vector2 curr = origin;
  for (int i = 0; i < cell_num.y; i++) {
    for (int j = 0; j < cell_num.x; j++) {
      cells[i][j].calculateSize(addVec(curr, line_thickness / 2),
                                addVec(spacing, -line_thickness));
      curr.x += spacing.x;
    }
    curr.y += spacing.y;
    curr.x = origin.x;
  }
}

// Gets the cell at the given screen location
cell2D *grid2D::getCell(Vector2 screen_pos) {
  Vector2 loc = getCellGridPos(screen_pos);
  return &(cells[loc.y][loc.x]);
}

// Gets the index ofthe grid cell at the at the given grid coordinates
Vector2 grid2D::getCellGridPos(Vector2 grid_pos) {
  Vector2 coords;
  coords.x = (int)((grid_pos.x - origin.x) / spacing.x);
  coords.y = (int)((grid_pos.y - origin.y) / spacing.y);
  return coords;
}

// Removes hilghting from all cells
void grid2D::unhighlight() {
  for (size_t i = 0; i < cells.size(); i++) {
    for (size_t j = 0; j < cells[i].size(); j++) {
      cells[i][j].highlight = false;
    }
  }
}

// Draws the grid
void grid2D::drawGrid2D() {
  for (size_t i = 0; i < cells.size(); i++) {
    for (size_t j = 0; j < cells[i].size(); j++) {
      cells[i][j].drawCell2D();
    }
  }

  drawOutlineGridLines2D(origin, grid_size, cell_num, line_marg, line_thickness, colour);
}

void grid2D::paintHighlighted(bool clear_mode, ElemCC::ColorVal painting_colour) {
  for (size_t i = 0; i < cells.size(); i++) {
    for (size_t j = 0; j < cells[i].size(); j++) {
      if (cells[i][j].highlight) {
        if (!clear_mode) {
          cells[i][j].painted = painting_colour;

        } else {
          if (cells[i][j].painted == painting_colour) {
            cells[i][j].painted = ElemCC::ColorVal::CELL_EMPTY;
          }
        }
      }
    }
  }
}

int grid2D::pressInputDown(int button, Vector2 mouse_pos, int global_hold) {
  if (!inArea(mouse_pos) || cells.empty()) {
    return 0;
  }
  Vector2 curr_coord = getCellGridPos(mouse_pos);
  cell2D curr_cell = cells[curr_coord.y][curr_coord.x];
  if (global_hold != -1 && board_hold == -1) {
    return 0;
  }
  if (board_hold == -1) {
    clear_mode = (curr_cell.painted == ElemCC::inputButtonColor[button]);
    start_cell_coord = curr_coord;
    board_hold = button;
  }

  unhighlight();
  Vector2 delta_coord = keepMaxMag(subVec(curr_coord, start_cell_coord));
  Vector2 increment = signVec(delta_coord);
  Vector2 cap = addVec(addVec(start_cell_coord, delta_coord), increment);
  Vector2 curr = start_cell_coord;

  do {
    cells[curr.y][curr.x].highlight = true;
    curr = addVec(curr, increment);
  } while ((!vecEquals(curr, cap)));

  return board_hold;
}

void grid2D::pressInputUp(int button, Vector2 mouse_pos) {
  if (board_hold == button) {
    paintHighlighted(clear_mode, ElemCC::inputButtonColor[board_hold]);
    board_hold = -1;
    unhighlight();
  }
}

// Checks if the mouse is on the grid
bool grid2D::inArea(Vector2 screen_pos) {
  return (screen_pos.x >= origin.x) &&
         (screen_pos.x < origin.x + grid_size.x) &&
         (screen_pos.y >= origin.y) &&
         (screen_pos.y < origin.y + grid_size.y);
}

#include "grid2D.h"
#include "helper/helper.h"
#include "helper/outlinedDraw.h"

// A grid made up of a collection if cells
// Current implementation takes into account the size of the labels
grid2D::grid2D(Vector2 loc, Vector2 board_size, Vector2 num_cells) {
  cell_num = num_cells;
  calculateGridSize(loc, board_size, num_cells);
}

// Calculate the dimensions and location of the grid
// Intended for when grid is initiazed or re-sized
void grid2D::calculateGridSize(Vector2 loc, Vector2 board_size, Vector2 num_cells) {
  cell_num = num_cells;
  spacing = divVec(board_size, cell_num);

  base_thick = minVec(spacing) / THICK_RATIO;
  line_marg = base_thick / LINE_MARG_RATIO;
  line_thickness = (base_thick + 2 * line_marg);
  origin = loc;
  grid_size = board_size;

  Vector2 curr = origin;
  for (int i = 0; i < cell_num.y; i++) {
    if (i >= cells.size()) {
      cells.push_back(std::vector<cell2D>());
    }
    for (int j = 0; j < cell_num.y; j++) {
      if (j >= cells[i].size()) {
        cells[i].push_back(cell2D(addVec(curr, line_thickness / 2), addVec(spacing, -line_thickness)));
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

// Checks if the mouse is on the grid
bool grid2D::inGrid(Vector2 screen_pos) {
  return (screen_pos.x >= origin.x) &&
         (screen_pos.x < origin.x + grid_size.x) &&
         (screen_pos.y >= origin.y) &&
         (screen_pos.y < origin.y + grid_size.y);
}

// Gets the cell at the given screen location
cell2D *grid2D::getCell(Vector2 screen_pos) {
  Vector2 loc = getCellGridPos(screen_pos);
  return &(cells[loc.y][loc.x]);
}

// Gets the top left corner of the grid at the at the given grid coordinate
Vector2 grid2D::getCellGridPos(Vector2 grid_pos) {
  Vector2 coords;
  coords.x = (int)((grid_pos.x - origin.x) / spacing.x);
  coords.y = (int)((grid_pos.y - origin.y) / spacing.y);
  return coords;
}

// Removes hilghting from all cells
void grid2D::unhighlight() {
  for (unsigned int i = 0; i < cells.size(); i++) {
    for (unsigned int j = 0; j < cells[i].size(); j++) {
      cells[i][j].highlight = false;
    }
  }
}

// Draws the grid
void grid2D::drawGrid2D() {
  for (std::vector<cell2D> row : cells) {
    for (cell2D entry : row) {
      entry.drawCell2D();
    }
  }

  drawOutlineGridLines2D(origin, grid_size, cell_num, line_marg, line_thickness, colour);
}

/*Vector2 curr_start = origin;
Vector2 curr_end = origin;

curr_start.y -= (base_thick / 2) + line_marg;
curr_end.y += grid_size.y + (base_thick / 2) + line_marg;
for (int i = 0; i <= cell_num.y; i++) {
  DrawLineEx(curr_start, curr_end, line_thickness, ElemCC::COLOUR_LOOKUP[colour]);

  curr_start.x += spacing.x;
  curr_end.x += spacing.x;
}

curr_start = origin;
curr_end = origin;
curr_start.x -= (base_thick / 2) + line_marg;
curr_end.x += grid_size.x + (base_thick / 2) + line_marg;

for (int i = 0; i <= cell_num.x; i++) {
  drawOutLineLine2D(curr_start, curr_end, line_marg, base_thick, colour);

  curr_start.y += spacing.y;
  curr_end.y += spacing.y;
}

curr_start = origin;
curr_end = origin;
curr_start.y -= (base_thick / 2) + line_marg;
curr_end.y += grid_size.y + (base_thick / 2) + line_marg;

for (int i = 0; i <= cell_num.y; i++) {
  drawSubLine2D(curr_start, curr_end, line_marg, base_thick, colour);

  curr_start.x += spacing.x;
  curr_end.x += spacing.x;
}*/

void grid2D::paintHighlighted(bool clear_mode, ElemCC::ColorVal painting_colour) {
  for (unsigned int i = 0; i < cells.size(); i++) {
    for (unsigned int j = 0; j < cells[i].size(); j++) {
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

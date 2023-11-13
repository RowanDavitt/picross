#include "cell2D.h"
#include "helper.h"

// Cells, the boxes inside of a grid
// pos: is x y coord of top left corner
// dimension: width (x), height (y)
// paint: color the cell should currently be
cell2D::cell2D(Vector2 pos, Vector2 dimension) {
  calculateSize(pos, dimension);
}

// Finds out what size the cell should be
// Intended for consturcting the cell and adjusting it's size
//
// pos: is x y coord of top left corner
// dimension: width (x), height (y)
void cell2D::calculateSize(Vector2 pos, Vector2 dimension) {
  cell_margin = dimension.x / C_MARG_RATIO;
  sub_margin = dimension.x / SUB_MARG_RATIO;

  cell.x = pos.x + cell_margin;
  cell.y = pos.y + cell_margin;
  cell.width = dimension.x - (2 * cell_margin);
  cell.height = dimension.y - (2 * cell_margin);

  subCell.x = cell.x + sub_margin;
  subCell.y = cell.y + sub_margin;
  subCell.width = cell.width - (2 * sub_margin);
  subCell.height = cell.height - (2 * sub_margin);
}

// Draws the cell, highlighting if needed
void cell2D::drawCell2D() {
  if (highlight) {
    DrawRectangleRec(cell, ElemCC::COLOUR_LOOKUP[ElemCC::CELL_HIGHLIGHT]);
  } else {
    DrawRectangleRec(cell, ElemCC::COLOUR_LOOKUP[painted]);
  }
  DrawRectangleRec(subCell, ElemCC::SUB_LOOKUP[painted]);
}
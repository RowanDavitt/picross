#include "labelSet.h"
#include "helper/helper.h"
#include "helper/outlinedDraw.h"

labelSet::labelSet(Vector2 loc, Vector2 l_spacing, Vector2 num_cells, int label_height, float l_thick, std::vector<std::vector<bool>> *input_puzzle) {
  cell_num = num_cells;
  puzzle = input_puzzle;
  calculateSize(loc, l_spacing, num_cells, label_height, l_thick);
}

void labelSet::calculateSize(Vector2 loc, Vector2 l_spacing, Vector2 num_cells, int label_height, float l_thick) {
  max_size.y = 0;
  max_size.x = 0;
  if (!(*puzzle).empty()) {

    for (size_t i = 0; i < (*puzzle).size(); i++) {
      if (i >= y_labels.size()) {
        y_labels.push_back(std::vector<int>());
      }
    }
    for (size_t i = 0; i < (*puzzle)[0].size(); i++) {
      if (i >= x_labels.size()) {
        x_labels.push_back(std::vector<int>());
      }
    }
    for (size_t i = 0; i < (*puzzle).size(); i++) {
      makeLabelY(i);
      if (y_labels[i].size() > max_size.y) max_size.y = y_labels[i].size();
    }
    for (size_t i = 0; i < (*puzzle)[0].size(); i++) {
      makeLabelX(i);
      if (x_labels[i].size() > max_size.x) max_size.x = x_labels[i].size();
    }
  }
  cell_num = num_cells;
  line_thick = l_thick;
  spacing = l_spacing;
  off = addVec(loc, -line_thick / 2);

  // char_size = getFontSize((spacing.x / max_size.y) - (max_size.y * STACK_SPACING), GetFontDefault());

  Vector2 char_prop = getMaxFontBox(GetFontDefault());
  char_size.y = (label_height / max_size.y) - STACK_SPACING;
  char_size.x = char_size.y * (char_prop.x / char_prop.y);
  char_outline = char_size.y / CHAR_OUTLINE_RATIO;
}

void labelSet::makeLabelX(size_t col) {
  x_labels[col].clear();
  size_t runSum = 0;
  for (std::vector<bool> row : (*puzzle)) {
    if (row[col]) {
      runSum++;
    } else {
      if (runSum > 0) {
        x_labels[col].push_back(runSum);
        runSum = 0;
      }
    }
  }
  if (runSum > 0 || x_labels[col].size() == 0) x_labels[col].push_back(runSum);
}

void labelSet::makeLabelY(size_t row) {
  y_labels[row].clear();
  size_t runSum = 0;
  for (bool entry : (*puzzle)[row]) {
    if (entry) {
      runSum++;
    } else {
      if (runSum > 0) {
        y_labels[row].push_back(runSum);
        runSum = 0;
      }
    }
  }

  if (runSum > 0 || y_labels[row].size() == 0) y_labels[row].push_back(runSum);
}

void labelSet::drawYLabel() {
  Vector2 curr = off;
  curr.y += (spacing.y - char_size.y + line_thick) / 2;

  for (std::vector<int> row : y_labels) {
    for (int i = row.size() - 1; i >= 0; i--) {
      std::string text = std::to_string(row[i]);
      int c_offset = MeasureText(text.c_str(), char_size.y);
      curr.x -= char_size.x;
      DrawSuperText(text.c_str(), curr, -c_offset / 2, char_size.y, char_outline, text_colour);
      curr.x -= STACK_SPACING;
    }
    curr.x = off.x;
    curr.y += spacing.y;
  }
}

void labelSet::drawXLabel() {
  Vector2 curr = off;
  curr.x += (spacing.x - char_size.x + line_thick) / 2;
  curr.y -= 0.5 * char_size.y;

  for (std::vector<int> col : x_labels) {
    for (int i = col.size() - 1; i >= 0; i--) {
      std::string text = std::to_string(col[i]);
      int c_offset = MeasureText(text.c_str(), char_size.y);
      curr.y -= char_size.y;
      DrawSuperText(text.c_str(), curr, c_offset / 2, char_size.y, char_outline, text_colour);
      curr.y -= STACK_SPACING;
    }
    curr.y = off.y - 0.5 * char_size.y;
    curr.x += spacing.x;
  }
}

Vector2 labelSet::getMaxSizeLabel(std::vector<std::vector<bool>> *puzzle) {
  Vector2 curr_sum{0, 0};
  Vector2 curr_max{0, 0};
  for (unsigned int y = 0; y < (*puzzle).size(); y++) {
    curr_sum = {0, 0};
    for (unsigned int x = 0; x < (*puzzle)[y].size(); x++) {
      if ((*puzzle)[y][x]) curr_sum.x++;
    }
    curr_max.x = max(curr_sum.x, curr_max.x);
  }
  for (unsigned int x = 0; x < (*puzzle)[0].size(); x++) {
    curr_sum = {0, 0};
    for (unsigned int y = 0; y < (*puzzle).size(); y++) {
      if ((*puzzle)[y][x]) curr_sum.y++;
    }
    curr_max.y = max(curr_sum.y, curr_max.y);
  }
  return curr_max;
}
#include "labelSet.h"
#include "helper/helper.h"
#include "helper/outlinedDraw.h"

labelSet::labelSet(Vector2 loc, Vector2 l_spacing, Vector2 num_cells, int label_height, float l_thick, std::vector<std::vector<bool>> *input_puzzle) {
  cell_num = num_cells;
  puzzle = input_puzzle;
  calculateSize(loc, l_spacing, num_cells, label_height, l_thick);
}

void labelSet::calculateSize(Vector2 loc, Vector2 l_spacing, Vector2 num_cells, int label_height, float l_thick) {
  labelHeight = label_height;
  max_size.y = 0;
  max_size.x = 0;
  stack_spacing = label_height * STACK_SPACING_RATIO;
  if (!puzzle->empty()) {

    for (size_t i = 0; i < puzzle->size(); i++) {
      if (i >= y_labels.size()) {
        y_labels.push_back(std::vector<int>());
      }
    }
    for (size_t i = 0; i < (*puzzle)[0].size(); i++) {
      if (i >= x_labels.size()) {
        x_labels.push_back(std::vector<int>());
      }
    }
    for (size_t i = 0; i < puzzle->size(); i++) {
      makeLabelY(i);
      max_size.y = max(y_labels[i].size(), max_size.y);
    }
    for (size_t i = 0; i < (*puzzle)[0].size(); i++) {
      makeLabelX(i);
      max_size.x = max(x_labels[i].size(), max_size.x);
    }
  }
  cell_num = num_cells;
  line_thick = l_thick;
  spacing = l_spacing;
  off = loc;
  char_box = min((labelHeight - stack_spacing) / maxVec(max_size), minVec(spacing));
  char_outline = char_box / CHAR_OUTLINE_RATIO;
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
  curr.y += ((spacing.y - char_box + line_thick) / 2);
  curr.x -= stack_spacing;

  for (std::vector<int> row : y_labels) {
    for (int i = row.size() - 1; i >= 0; i--) {
      std::string text = std::to_string(row[i]);
      // curr.x -= c_offset;
      curr.x -= char_box;
      drawTextInBound(text.c_str(), setBothVec(char_box), curr, char_outline, 1, text_colour);
    }
    curr.x = off.x - stack_spacing;
    curr.y += spacing.y;
  }
}

void labelSet::drawXLabel() {
  Vector2 curr = off;
  curr.x += (line_thick) / 2;
  curr.y -= stack_spacing;

  for (std::vector<int> col : x_labels) {
    for (int i = col.size() - 1; i >= 0; i--) {
      std::string text = std::to_string(col[i]);
      curr.y -= char_box;
      drawTextInBound(text.c_str(), setBothVec(char_box), curr, char_outline, 1, text_colour);
    }
    curr.y = off.y - stack_spacing;
    curr.x += spacing.x;
  }
}

Vector2 labelSet::getMaxSizeLabel(std::vector<std::vector<bool>> *puzzle) {
  Vector2 curr_sum{0, 0};
  Vector2 curr_max{0, 0};
  for (size_t y = 0; y < (*puzzle).size(); y++) {
    curr_sum = {0, 0};
    for (size_t x = 0; x < (*puzzle)[y].size(); x++) {
      if ((*puzzle)[y][x]) curr_sum.x++;
    }
    curr_max.x = max(curr_sum.x, curr_max.x);
  }
  for (size_t x = 0; x < (*puzzle)[0].size(); x++) {
    curr_sum = {0, 0};
    for (size_t y = 0; y < (*puzzle).size(); y++) {
      if ((*puzzle)[y][x]) curr_sum.y++;
    }
    curr_max.y = max(curr_sum.y, curr_max.y);
  }
  return curr_max;
}
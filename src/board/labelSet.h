#include "helper/ColorConsts.h"
#include "raylib.h"
#include <vector>

#ifndef LABEL_SET
#define LABEL_SET
class labelSet {
private:
  std::vector<std::vector<int>> y_labels;
  std::vector<std::vector<int>> x_labels;
  std::vector<std::vector<bool>> *puzzle;

public:
  static const int STACK_SPACING = 8;
  static const int CHAR_OUTLINE_RATIO = 8;
  float char_outline;
  float line_thick;
  ElemCC::ColorVal text_colour = ElemCC::ColorVal::LABEL_TEXT;
  Vector2 spacing;
  Vector2 off;
  Vector2 max_size;
  Vector2 char_size;
  Vector2 cell_num;

  labelSet(Vector2 loc, Vector2 spacing, Vector2 num_cells, int label_height, float l_thick, std::vector<std::vector<bool>> *input_puzzle);
  labelSet() {}
  void calculateSize(Vector2 loc, Vector2 l_spacing, Vector2 num_cells, int label_height, float l_thick);
  void makeLabelX(int col);
  void makeLabelY(int row);
  void drawYLabel();
  void drawXLabel();
  static Vector2 getMaxSizeLabel(std::vector<std::vector<bool>> *puzzle);
};
#endif
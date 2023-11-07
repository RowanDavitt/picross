#include "raylib.h"
#include "ColorConsts.h"
#include <vector>

#ifndef LABEL_SET
#define LABEL_SET
class labelSet{
    private:
        std::vector<std::vector<int>> y_labels;
        std::vector<std::vector<int>> x_labels;
        std::vector<std::vector<bool>>* puzzle;
    public:
        static const int STACK_SPACING = 8;
        static const int CHAR_MARGIN_RATIO = 14;
        float char_margin;
        float line_thick;
        ElemCC::ColorVal text_colour = ElemCC::ColorVal::LABEL_TEXT;
        Vector2 spacing;
        Vector2 off;
        Vector2 max_size;
        Vector2 char_size;
        Vector2 cell_num;

        labelSet(Vector2 loc, Vector2 dimensions, Vector2 spacing, Vector2 num_cells, float l_thick, std::vector<std::vector<bool>>* input_puzzle);
        labelSet(){}
        void calculateSize(Vector2 loc, Vector2 dimensions, Vector2 l_spacing, float l_thick);
        void makeLabelX(int col);
        void makeLabelY(int row);
        void drawYLabel();
        void drawXLabel();
        void DrawSuperText(const char* text, Vector2 loc, int offset, Vector2 char_size, ElemCC::ColorVal text_colour);
        static Vector2 getMaxSizeLabel(std::vector<std::vector<bool>>* puzzle);
};
#endif
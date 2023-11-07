#include "labelSet.h"
#include "helper.h"
#include <string>

labelSet::labelSet(Vector2 loc, Vector2 dimensions, Vector2 l_spacing, Vector2 num_cells, float l_thick, std::vector<std::vector<bool>>* input_puzzle){
    cell_num = num_cells;
    puzzle = input_puzzle;

    max_size.y = 0;
    for (int i = 0; i < (int)(*puzzle).size(); i++){
        y_labels.push_back(std::vector<int>());
        x_labels.push_back(std::vector<int>());
    }
    for (int i = 0; i < (int)(*puzzle).size(); i++){
        makeLabelY(i);
        if (y_labels[i].size() > max_size.y) max_size.y = y_labels[i].size();

    }
    max_size.x =0;
    for (int i = 0; i < (int)puzzle[0].size(); i++){
        makeLabelX(i);
        if (x_labels[i].size() > max_size.x) max_size.x = x_labels[i].size();
    }
    calculateSize(loc, dimensions, l_spacing, l_thick);
}

void labelSet::calculateSize(Vector2 loc, Vector2 dimensions, Vector2 l_spacing, float l_thick){
    line_thick = l_thick;
    spacing = l_spacing;
    off = addVec(loc, -line_thick/2);

    char_size = getFontSize((spacing.x/max_size.y) - (max_size.y * STACK_SPACING), GetFontDefault());
    off = addVec(spacing, off);
    char_margin = char_size.y/CHAR_MARGIN_RATIO;

}

void labelSet::makeLabelX(int col){
    int runSum = 0;
    for (std::vector<bool> row: (*puzzle)){
        if (row[col]){
            runSum++;
        }else{
            if (runSum > 0){
                x_labels[col].push_back(runSum);
                runSum = 0;
            }
        }
    }
    if (runSum > 0 || x_labels[col].size() == 0) x_labels[col].push_back(runSum);
}

void labelSet::makeLabelY(int row){
    int runSum = 0;
    for (bool entry : (*puzzle)[row]){
        if (entry){
            runSum++;
        }else{
            if (runSum > 0){
                y_labels[row].push_back(runSum);
                runSum = 0;
            }
        }
    }

    if (runSum > 0 || y_labels[row].size() == 0) y_labels[row].push_back(runSum);
}

void labelSet::drawYLabel(){
    Vector2 curr = off;
    curr.y += (spacing.y- char_size.y + line_thick)/2;

    for (std::vector<int> row : y_labels){
        for (int i = row.size()-1; i >= 0; i-- ){
            std::string text = std::to_string(row[i]);
            int c_offset = MeasureText(text.c_str(), char_size.y);
            curr.x -= char_size.x;
            DrawSuperText(text.c_str(), curr, -c_offset/2, char_size, text_colour);
            curr.x -= STACK_SPACING;
        }
        curr.x = off.x;
        curr.y += spacing.y;
    }
}

void labelSet::drawXLabel(){
    Vector2 curr = off;
    curr.x += (spacing.x - char_size.x + line_thick)/2;
    curr.y -= 0.5*char_size.y;

    for (std::vector<int> col : x_labels){
        for (int i = col.size()-1; i >= 0; i-- ){
            std::string text = std::to_string(col[i]);
            int c_offset = MeasureText(text.c_str(), char_size.y);
            curr.y -= char_size.y;
            DrawSuperText(text.c_str(), curr, c_offset/2, char_size, text_colour);
            curr.y -= STACK_SPACING;
        }
        curr.y = off.y - 0.5*char_size.y;
        curr.x += spacing.x;
    }
}

//outlines text
void labelSet::DrawSuperText(const char* text, Vector2 loc, int offset, Vector2 char_size, ElemCC::ColorVal text_colour){
    loc.x+= offset;
    for (int i = -char_margin; i<= char_margin; i++)for (int j = -char_margin; j<= char_margin; j++){
        DrawText(text, loc.x +i, loc.y + j, char_size.y, ElemCC::COLOUR_LOOKUP[text_colour]);
    }

    DrawText(text, loc.x, loc.y, char_size.y, ElemCC::SUB_LOOKUP[text_colour]);
}

Vector2 labelSet::getMaxSizeLabel(std::vector<std::vector<bool>>* puzzle){
    Vector2 curr_sum {0,0};
    Vector2 curr_max {0,0};
    for (unsigned int y = 0; y < (*puzzle).size(); y++){
        curr_sum = {0,0};
        for (unsigned int x = 0; x < (*puzzle)[y].size(); x++){
            if ((*puzzle)[y][x]) curr_sum.x++;
        }
        curr_max.x = max(curr_sum.x, curr_max.x);
    }
    for (unsigned int x = 0; x < (*puzzle)[0].size(); x++){
        curr_sum = {0,0};
        for (unsigned int y =0; y < (*puzzle).size(); y++){
            if ((*puzzle)[y][x]) curr_sum.y++;
        }
        curr_max.y = max(curr_sum.y, curr_max.y);
    }
    return curr_max;
}
#include "grid2D.h"
#include "helper.h"

grid2D::grid2D(Vector2 loc, Vector2 board_size, Vector2 num_cells, Vector2 m_labels){
    max_labels = m_labels;
    cell_num = num_cells;
    calculateGridSize(loc, board_size);
    line_thickness = (base_thick + line_marg);

    Vector2 curr = origin;
    for (int i = 0; i < cell_num.y; i++){
        cells.push_back(std::vector<cell2D>());
        for (int j = 0; j < cell_num.y; j++){
            cells[i].push_back(cell2D(addVec(curr, line_thickness/2),  addVec(spacing, -line_thickness), ElemCC::ColorVal::CELL_EMPTY));
            curr.x += spacing.x;
        }
        curr.y += spacing.y;
        curr.x = origin.x;
    }
}

void grid2D::calculateGridSize(Vector2 loc, Vector2 board_size){
    spacing = divVec(board_size,addVec(cell_num, divVec(max_labels,3)));

    Vector2 label_thick = scaleVec(divVec(spacing,3), max_labels);
    base_thick = minVec(spacing)/THICK_RATIO;
    line_marg = base_thick/LINE_MARG_RATIO;
    origin = addVec(loc,label_thick);
    grid_size = subVec(board_size, label_thick);

}

void grid2D::recalculateCellSize(){
    float line_thickness = (base_thick + line_marg);
    Vector2 curr = origin;
    for (int i = 0; i < cell_num.y; i++){
        for (int j = 0; j < cell_num.y; j++){
            cells[i][j].calculateSize(addVec(curr, line_thickness/2),  addVec(spacing, -line_thickness));
            curr.x += spacing.x;
        }
        curr.y += spacing.y;
        curr.x = origin.x;
    }
}


bool grid2D::onBoard(Vector2 screen_pos){
    return (screen_pos.x >= origin.x) && (screen_pos.x < origin.x + grid_size.x) && (screen_pos.y >= origin.y) && (screen_pos.y < origin.y + grid_size.y);

}

cell2D* grid2D::getCell(Vector2 screen_pos){
    Vector2 loc = getCellGridPos(screen_pos);
    return &(cells[loc.y][loc.x]);

}

Vector2 grid2D::getCellGridPos(Vector2 grid_pos){
    Vector2 coords;
    coords.x = (int)((grid_pos.x - origin.x) / spacing.x);
    coords.y = (int)((grid_pos.y - origin.y) / spacing.y);
    return coords;

}

void grid2D::unhighlight(){
    for (unsigned int i = 0; i < cells.size(); i++){
        for (unsigned int j = 0; j < cells[i].size(); j++){
            cells[i][j].highlight = false;
        }
    }
}

void grid2D::drawGrid2D(){

    for (std::vector<cell2D> row : cells){
        for (cell2D entry : row){
            entry.drawCell2D();
        }
    }

    Vector2 curr_start = origin;
    Vector2 curr_end = origin;

    curr_start.y -= (base_thick/2)+ line_marg;
    curr_end.y += grid_size.y+ (base_thick/2)+ line_marg;
    for (int i = 0; i <= cell_num.y; i++){
        DrawLineEx(curr_start, curr_end, base_thick + 2* line_marg, ElemCC::COLOUR_LOOKUP[colour]);

        curr_start.x += spacing.x;
        curr_end.x += spacing.x;
    }

    curr_start = origin;
    curr_end = origin;

    curr_start.x -= (base_thick/2)+ line_marg;
    curr_end.x += grid_size.x+ (base_thick/2)+ line_marg;
    for (int i = 0; i <= cell_num.x; i++){
        DrawLineEx(curr_start, curr_end, base_thick + 2*line_marg, ElemCC::COLOUR_LOOKUP[colour]);

        curr_start.y += spacing.y;
        curr_end.y += spacing.y;
        
    }

    curr_start = origin;
    curr_end = origin;

    curr_end.y += grid_size.y+(base_thick/2);
    curr_start.y -= (base_thick/2);
    for (int i = 0; i <= cell_num.y; i++){
        DrawLineEx(curr_start, curr_end, base_thick, ElemCC::SUB_LOOKUP[colour]);
        
        curr_start.x += spacing.x;
        curr_end.x += spacing.x;
    }

    curr_start = origin;
    curr_end = origin;

    curr_end.x += grid_size.x+(base_thick/2);
    curr_start.x -= (base_thick/2);
    for (int i = 0; i <= cell_num.x; i++){
        DrawLineEx(curr_start, curr_end, base_thick, ElemCC::SUB_LOOKUP[colour]);

        curr_start.y += spacing.y;
        curr_end.y += spacing.y;
    }
}
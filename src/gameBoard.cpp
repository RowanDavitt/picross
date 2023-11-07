#include "gameBoard.h"
#include "helper.h"

gameBoard::gameBoard(std::vector<std::vector<bool>>* input_puzzle){
    puzzle = *input_puzzle;
    calculateGameBoard();
    Vector2 max_labels = labelSet::getMaxSizeLabel(input_puzzle);

    grid = grid2D(origin, board_size, num_cells, max_labels);
    labels = labelSet(origin, board_size, grid.spacing, num_cells, grid.line_thickness,  input_puzzle);
    
}

void gameBoard::recalculateElements(){

    grid.calculateGridSize(origin, board_size);
    grid.recalculateCellSize();

    labels.calculateSize(origin, board_size, grid.spacing,grid.line_thickness);
}

void gameBoard::calculateGameBoard(){
    margin = min(GetScreenHeight(),GetScreenWidth())/MARGIN_RATIO;
    float grid_base = min(GetScreenWidth(),GetScreenHeight());
    origin = {
        ((GetScreenWidth() - grid_base)/2 + margin),
        ((GetScreenHeight() - grid_base)/2 + margin)
    };

    board_size = {
        (GetScreenWidth() - (2*origin.x)),
        (GetScreenHeight() - (2*origin.y))
    };

    num_cells = {
        (float)(puzzle)[0].size(),
        (float)(puzzle).size()
    };
}


void gameBoard::drawGameBoard(){
    labels.drawXLabel();
    labels.drawYLabel();
    grid.drawGrid2D();

}

std::vector<std::vector<bool>> gameBoard::getBoardState(){
    std::vector<std::vector<bool>> b_state;
    for (unsigned int y = 0; y < grid.cells.size(); y++){
        b_state.push_back(std::vector<bool>());
        for (unsigned int x = 0; x < grid.cells[y].size(); x++){
            b_state[y].push_back(grid.cells[y][x].painted == ElemCC::ColorVal::CELL_FILL);
            
        }
    }
    return b_state;
}

bool gameBoard::checkWin(){
    std::vector<std::vector<bool>> b_state = getBoardState();
    bool win = true;
    for (unsigned int y = 0; y < b_state.size(); y++){
        for (unsigned int x = 0; x < b_state[y].size(); x++){
            win = win && (b_state[y][x] == puzzle[y][x]);
        }
    }
    return win;
}
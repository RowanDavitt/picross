#include "raylib.h"
#include "grid2D.h"
#include "labelSet.h"
#include "ColorConsts.h"

#ifndef GAME_BOARD
#define GAME_BOARD

class gameBoard{
    public:
        Vector2 spacing;
        Vector2 origin;
        Vector2 grid_size;
        Vector2 board_size;
        Vector2 grid_origin;
        Vector2 num_cells;
        grid2D grid;
        labelSet labels;
        const static int MARGIN_RATIO = 12;
        int margin;
        std::vector<std::vector<bool>> puzzle;
        
        gameBoard(std::vector<std::vector<bool>>* input_puzzle);
        gameBoard(){}
        void calculateGameBoard();
        void recalculateElements();
        void drawGameBoard();
        std::vector<std::vector<bool>> getBoardState();
        bool checkWin();

};

#endif
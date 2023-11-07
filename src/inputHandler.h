#include"raylib.h"
#include "gameboard.h"

#ifndef INPUT_HANDLER
#define INPUT_HANDLER
class inputHandler{
    bool held = false;
    ElemCC::ColorVal painting_colour;
    Vector2 start_cell_coord;
    bool clear_mode;
    gameBoard *board;
public:
    void checkClick(int button, ElemCC::ColorVal paint);
    inputHandler(){};
    inputHandler(gameBoard *in_board);
    void paintHighlighted();

};
#endif
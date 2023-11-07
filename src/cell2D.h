#include "raylib.h"
#include "ColorConsts.h"

#ifndef CELL_2D
#define CELL_2D
class cell2D{
    private:
        Rectangle cell;
        Rectangle subCell;
    public:
        static const int C_MARG_RATIO = 8;
        static const int SUB_MARG_RATIO = 16;

        bool highlight = false;
        float cell_margin = 10;
        float sub_margin = 6;

            ElemCC::ColorVal painted = ElemCC::ColorVal::CELL_EMPTY;
        
        Color f_colour;
        cell2D(Vector2 pos, Vector2 dimension, ElemCC::ColorVal paint);
        void calculateSize(Vector2 pos, Vector2 dimension);
        void drawCell2D();
        cell2D(){}
};
#endif
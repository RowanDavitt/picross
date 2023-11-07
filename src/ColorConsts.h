#include "raylib.h"

#ifndef COLOUR_CONST
#define COLOUR_CONST
namespace MyColour{ //rgba
    const Color SOLID_WHITE {120,144,133,255};
    const Color GREYISH {187,176,190,255};
    const Color SUBTLE_GREY {50, 10, 57, 255};
    const Color LIGHT_GREY {130, 136, 133, 255};
    const Color MY_RED {255, 50, 50, 255};
    const Color HIGHLIGHTER_YELLOW {255, 255, 0, 255};
    const Color BLUEY_BLACK {37,0,43,255};

    const Color LIQUID_WHITE {237,243,254,255};
    const Color GREYISHER {205,190,210,255};
    const Color SUBTLER_GREYER {45, 7, 51, 255}; 
    const Color LIGHTERER_GREY {160, 166, 163, 255};
    const Color MY_WEAKER_RED {255, 100, 100, 255};
}
namespace ElemCC{
    enum ColorVal:int {CELL_EMPTY, CELL_FILL, CELL_BLOCK, CELL_HIGHLIGHT, BACKGROUND_FILL, GRID_LINES, LABEL_TEXT};
    const Color COLOUR_LOOKUP[] ={
        MyColour::SUBTLE_GREY,            //Cell Empty
        MyColour::GREYISH,              //Cell Filled
        MyColour::MY_RED,               //Cell Blocked
        MyColour::HIGHLIGHTER_YELLOW,   //Cell Highlight
        MyColour::BLUEY_BLACK,          //Background Fill
        MyColour::LIGHT_GREY,            //Grid Line
        MyColour::SOLID_WHITE,          //Label Text
    };

    const Color SUB_LOOKUP[] ={ // a secondary color for the inside area of a cell.
        MyColour::SUBTLER_GREYER,            //Cell Empty
        MyColour::GREYISHER,              //Cell Filled
        MyColour::MY_WEAKER_RED,               //Cell Blocked 
        MyColour::HIGHLIGHTER_YELLOW,   //Cell Highlight
        MyColour::BLUEY_BLACK,          //Background Fill
        MyColour::LIGHTERER_GREY,            //Grid Line
        MyColour::LIQUID_WHITE,          //Label Text
    };
}
#endif

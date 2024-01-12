#include "raylib.h"

#ifndef COLOUR_CONST
#define COLOUR_CONST

namespace MyColour { // {r,g,b,a} format

const Color SOLID_WHITE{93, 104, 103, 255};       // White, (it's acually grey)
const Color GREYISH{187, 176, 190, 255};          // A light grey
const Color SUBTLE_GREY{50, 10, 57, 255};         // Also grey (close to the bluey black)
const Color LIGHT_GREY{130, 136, 133, 255};       // Even more grey
const Color MY_RED{255, 50, 50, 255};             // At least its not grey (yet)
const Color HIGHLIGHTER_YELLOW{255, 255, 0, 255}; // Yellow (also not grey)
const Color BLUEY_BLACK{37, 0, 43, 255};          // Like a purpley blue-ish black

const Color LIQUID_WHITE{237, 243, 254, 255};   // Like solid white but melted
const Color GREYISHER{205, 190, 210, 255};      // Another grey
const Color SUBTLER_GREYER{45, 7, 51, 255};     // Not grey enough
const Color LIGHTERER_GREY{160, 166, 163, 255}; // Why do I need more grey
const Color MY_WEAKER_RED{255, 100, 100, 255};  // I miss the grey

} // namespace MyColour

namespace ElemCC { // Elemant Colour Constant
enum ColorVal : int {

  CELL_EMPTY,      // 0
  CELL_FILL,       // 1
  CELL_BLOCK,      // 2
  CELL_HIGHLIGHT,  // 3
  BACKGROUND_FILL, // 4
  GRID_LINES,      // 5
  LABEL_TEXT       // 6

};

// The main color of an element,
// If the element has a seperate sub-colour, this becomes the outer edge (atleast thats the intent)
const Color COLOUR_LOOKUP[] = {

    MyColour::SUBTLE_GREY,        // Cell Empty
    MyColour::GREYISH,            // Cell Filled
    MyColour::MY_RED,             // Cell Blocked
    MyColour::HIGHLIGHTER_YELLOW, // Cell Highlight
    MyColour::BLUEY_BLACK,        // Background Fill
    MyColour::LIGHT_GREY,         // Grid Line
    MyColour::SOLID_WHITE,        // Label Text
};

// A secondary color for inside fills
const Color SUB_LOOKUP[] = {

    MyColour::SUBTLER_GREYER,     // Cell Empty
    MyColour::GREYISHER,          // Cell Filled
    MyColour::MY_WEAKER_RED,      // Cell Blocked
    MyColour::HIGHLIGHTER_YELLOW, // Cell Highlight
    MyColour::BLUEY_BLACK,        // Background Fill
    MyColour::LIGHTERER_GREY,     // Grid Line
    MyColour::LIQUID_WHITE,       // Label Text

};

const ColorVal inputButtonColor[] = {
    CELL_FILL,
    CELL_BLOCK,
};

} // namespace ElemCC
#endif

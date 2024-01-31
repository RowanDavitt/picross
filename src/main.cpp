/*******************************************************************************************
 *
 *   raylib [core] example - Basic 3d example
 *
 *   Welcome to raylib!
 *
 *   To compile example, just press F5.
 *   Note that compiled executable is placed in the same folder as .c file
 *
 *   You can find all basic examples on C:\raylib\raylib\examples folder or
 *   raylib official webpage: www.raylib.com
 *
 *   Enjoy using raylib. :)
 *
 *   This example has been created using raylib 1.0 (www.raylib.com)
 *   raylib is licensed under an unmodified zlib/libpng license (View raylib.h for details)
 *
 *   Copyright (c) 2013-2023 Ramon Santamaria (@raysan5)
 *
 ********************************************************************************************/

#include "board/cell2D.h"
#include "board/gameBoard.h"
#include "board/grid2D.h"
#include "helper/ColorConsts.h"
#include "helper/helper.h"
#include "input/fileInput.h"
#include "input/inputHandler.h"
#include "loadPage/loadingPage.h"
#include "raylib.h"
#include <iostream>
#include <string>

#if defined(PLATFORM_WEB)
#include <emscripten/emscripten.h>
#endif

//----------------------------------------------------------------------------------
// Local Variables Definition (local to this module)
//----------------------------------------------------------------------------------
Camera2D camera = {0};

float margin;
gameBoard board;
inputHandler inputter;
puzzleLoader plzload;
bool set = false;

//----------------------------------------------------------------------------------
// Local Functions Declaration
//----------------------------------------------------------------------------------
static void UpdateDrawFrame(void); // Update and draw one frame

//----------------------------------------------------------------------------------
// Main entry point
//----------------------------------------------------------------------------------
int main() {
  std::vector<std::vector<bool>> input_puzzle;
  // readPuzzleFile("puzzles/testing2.pzl", &input_puzzle);
  //  Initialization
  //--------------------------------------------------------------------------------------
  const int screenWidth = 1080;
  const int screenHeight = 720;

  SetConfigFlags(FLAG_WINDOW_RESIZABLE);
  InitWindow(screenWidth, screenHeight, "Picross?");
  camera.offset = Vector2{0, 0};
  // camera.rotation = 90;
  camera.zoom = 1.0;
  camera.target = Vector2{0, 0};

  board = gameBoard(&input_puzzle);
  inputter = inputHandler(&board);
  plzload = puzzleLoader(&input_puzzle);
  inputter.addRegion(&plzload);

  //--------------------------------------------------------------------------------------

#if defined(PLATFORM_WEB)
  emscripten_set_main_loop(UpdateDrawFrame, 60, 1);
#else
  SetTargetFPS(60); // Set our game to run at 60 frames-per-second
  //--------------------------------------------------------------------------------------

  // Main game loop
  while (!WindowShouldClose()) // Detect window close button or ESC key
  {
    UpdateDrawFrame();
  }
#endif

  // De-Initialization
  //--------------------------------------------------------------------------------------
  CloseWindow(); // Close window and OpenGL context
  //--------------------------------------------------------------------------------------

  return 0;
}

// Update and draw game frame
static void UpdateDrawFrame(void) {
  // Update
  //----------------------------------------------------------------------------------
  // UpdateCamera2D(&camera, CAMERA_ORTHOGRAPHIC);
  //----------------------------------------------------------------------------------

  // Draw
  //----------------------------------------------------------------------------------
  BeginDrawing();

  ClearBackground(ElemCC::COLOUR_LOOKUP[ElemCC::ColorVal::BACKGROUND_FILL]);

  BeginMode2D(camera);
  //(*(board.getCell(GetMousePosition()))).painted = true;
  inputter.checkClick();
  if (plzload.done) {
    if (!set) {
      int temp2 = board.puzzle->size();
      board.calculateGameBoard();
      board.recalculateElements();
      set = true;
    }
    board.boardFrame();
  } else {
    plzload.LoadPageFrame();
  }

  // if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT) || IsMouseButtonReleased(MOUSE_BUTTON_RIGHT)) clear_paint = cell2D::EMPTY;

  EndMode2D();

  DrawFPS(10, 10);
  // DrawText(listPzLnames().c_str(), 10, 100, 30, WHITE);

  EndDrawing();
  //----------------------------------------------------------------------------------
}

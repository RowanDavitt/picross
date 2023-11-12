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

#include "ColorConsts.h"
#include "cell2D.h"
#include "gameBoard.h"
#include "grid2D.h"
#include "helper.h"
#include "inputHandler.h"
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

//----------------------------------------------------------------------------------
// Local Functions Declaration
//----------------------------------------------------------------------------------
static void UpdateDrawFrame(void); // Update and draw one frame

//----------------------------------------------------------------------------------
// Main entry point
//----------------------------------------------------------------------------------
int main() {
  std::vector<std::vector<bool>> input_puzzle = {{1, 0, 1, 1}, {1, 0, 0, 1}, {1, 1, 0, 1}, {0, 0, 1, 0}};
  // Initialization
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
  if (IsWindowResized()) {
    board.calculateGameBoard();
    board.recalculateElements();
  }

  inputter.checkClick(MOUSE_BUTTON_LEFT, ElemCC::ColorVal::CELL_FILL);
  inputter.checkClick(MOUSE_BUTTON_RIGHT, ElemCC::ColorVal::CELL_BLOCK);

  if (board.checkWin()) {
    DrawText("win", 10, 100, 20, RAYWHITE);
  }

  // if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT) || IsMouseButtonReleased(MOUSE_BUTTON_RIGHT)) clear_paint = cell2D::EMPTY;

  board.drawGameBoard();

  EndMode2D();

  DrawFPS(10, 10);

  EndDrawing();
  //----------------------------------------------------------------------------------
}

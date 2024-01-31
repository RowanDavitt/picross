
#ifndef LOADPAGE
#define LOADPAGE
#include "input/inputHandler.h"
#include "loadFileButton.h"
#include <string>
#include <vector>
class puzzleLoader : public inputArea {
  std::string selectTitle = "Select a File";
  std::vector<std::string> fileList;
  std::vector<fileButton> fileButtonList;
  std::string prefix = "puzzles/";

public:
  int done = 0;
  float text_height = 35;
  std::vector<std::vector<bool>> *puzzle;
  puzzleLoader(std::vector<std::vector<bool>> *puzzleDest);
  puzzleLoader(){};

  int LoadPageFrame();
  void drawTitle();
  void makeOptionList();
  void resize();
  void drawList();
  void checkInputs();

  bool inArea(Vector2 location);
  int pressInputDown(int button, Vector2 mouse_pos, int global_hold);
  void pressInputUp(int button);
};

#endif
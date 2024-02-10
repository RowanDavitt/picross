
#ifndef LOADPAGE
#define LOADPAGE
#include "input/inputHandler.h"
#include "input/textButton.h"
#include <list>
#include <string>
#include <vector>
class puzzleLoader {
  std::string selectTitle = "Select a Puzzle";
  std::vector<std::string> fileList;
  std::list<textButton> fileButtonList;
  inputHandler inputter = inputHandler();
  size_t buttonListSize = 0;
  float BUTTON_X_SIZE_RATIO = 0.5;

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
};

#endif
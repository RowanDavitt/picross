
#ifndef LOADPAGE
#define LOADPAGE
#include "input/inputHandler.h"
#include "loadFileButton.h"
#include <list>
#include <string>
#include <vector>
class puzzleLoader {
  std::string selectTitle = "Select a File";
  std::vector<std::string> fileList;
  std::list<fileButton> fileButtonList;
  std::string prefix = "puzzles/";
  inputHandler inputter = inputHandler();
  size_t buttonListSize = 0;

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
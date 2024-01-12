#ifndef INPUT_HANDLER
#define INPUT_HANDLER
#include "board/gameboard.h"
#include "inputArea.h"
#include "raylib.h"

class inputHandler {
private:
  int mouse_buttons[2] = {MOUSE_BUTTON_LEFT, MOUSE_BUTTON_RIGHT};
  int global_hold = -1;
  std::vector<inputArea *> regions;
  std::vector<std::vector<inputArea *>> releaseNotifyRegions = std::vector<std::vector<inputArea *>>(2, std::vector<inputArea *>());

public:
  inputHandler() {}
  inputHandler(std::vector<inputArea *> in_regions);
  inputHandler(inputArea *region);
  void checkClick();
  void inputDownRegions(int button, Vector2 loc);
  void inputUpRegions(int button);
};
#endif
#include "inputHandler.h"
#include <string>

inputHandler::inputHandler(std::vector<inputArea *> in_regions) {
  regions = in_regions;
}

inputHandler::inputHandler() {
  regions = std::vector<inputArea *>();
}

inputHandler::inputHandler(inputArea *region) {
  regions.push_back(region);
}

void inputHandler::addRegion(inputArea *region) {
  regions.push_back(region);
}

void inputHandler::inputDownRegions(int button, Vector2 loc) {
  for (inputArea *IA : regions) {
    if (IA->inArea(loc)) {
      if (IA->pressInputDown(button, loc, global_hold) != -1) {
        releaseNotifyRegions[button].push_back(IA);
      }
    }
  }
}

void inputHandler::inputUpRegions(int button, Vector2 loc) {
  for (inputArea *IA : releaseNotifyRegions[button]) {
    IA->pressInputUp(button, loc);
  }
  releaseNotifyRegions[button].clear();
}

void inputHandler::checkClick() {
  Vector2 loc = GetMousePosition();
  for (int m_button : mouse_buttons) {
    if (IsMouseButtonDown(m_button)) {
      inputDownRegions(m_button, loc);
      global_hold = m_button;

    } else {
      inputUpRegions(m_button, loc);
      if (global_hold == m_button) {
        global_hold = -1;
      }
    }
  }
}

#include "loadingPage.h"
#include "helper/outlinedDraw.h"
#include "input/fileInput.h"

puzzleLoader::puzzleLoader(std::vector<std::vector<bool>> *puzzleDest) {
  fileList = std::vector<std::string>();
  fileButtonList = std::vector<fileButton>();
  puzzle = puzzleDest;
  listPzLnames(&fileList);
  makeOptionList();
  done = 0;
}

void puzzleLoader::makeOptionList() {
  float text_Y_increment = (GetScreenHeight() / (3 + fileList.size()));
  float text_X_loc = GetScreenWidth() / 3;
  Vector2 pos = {text_X_loc, 2 * text_Y_increment};
  Vector2 size = {text_X_loc, text_Y_increment};
  for (std::string lfile : fileList) {
    fileButtonList.emplace_back(pos, size, lfile);
    pos.y += text_Y_increment;
  }
}

int puzzleLoader::LoadPageFrame() {
  if (IsWindowResized()) {
    resize();
  }

  drawTitle();
  drawList();
  checkInputs();
  return done;
}

void puzzleLoader::drawList() {
  for (size_t i = 0; i < fileButtonList.size(); i++) {
    fileButtonList[i].draw();
  }
}

void puzzleLoader::checkInputs() {
  for (size_t i = 0; i < fileButtonList.size(); i++) {
    if (fileButtonList[i].done) {
      readPuzzleFile(prefix + fileButtonList[i].fileName, puzzle);
      done = 1;
      return;
    }
  }
}

void puzzleLoader::resize() {
  float text_Y_increment = (GetScreenHeight() / (3 + fileList.size()));
  float text_X_loc = GetScreenWidth() / 3;
  Vector2 pos = {text_X_loc, 2 * text_Y_increment};
  Vector2 size = {text_X_loc, text_Y_increment};
  for (size_t i = 0; i < fileButtonList.size(); i++) {
    fileButtonList[i].resize(pos, size);
    pos.y += text_Y_increment;
  }
}

void puzzleLoader::drawTitle() {
  float text_Y_loc_increment = (GetScreenHeight() / (3 + fileList.size()));
  float text_X_loc = ((GetScreenWidth() - MeasureText(selectTitle.c_str(), text_height)) / 2) + 3;
  Vector2 textLoc = {text_X_loc, text_Y_loc_increment};
  DrawSuperText(selectTitle.c_str(), textLoc, 0, text_height, 3, ElemCC::LABEL_TEXT);
}

bool puzzleLoader::inArea(Vector2 location) {
  for (size_t i = 0; i < fileButtonList.size(); i++) {
    if (fileButtonList[i].inArea(location)) {
      return true;
    }
  }
  return false;
}

int puzzleLoader::pressInputDown(int button, Vector2 mouse_pos, int global_hold) {
  for (size_t i = 0; i < fileButtonList.size(); i++) {
    fileButtonList[i].pressInputDown(button, mouse_pos);
  }
  return -1;
}
void puzzleLoader::pressInputUp(int button) {}
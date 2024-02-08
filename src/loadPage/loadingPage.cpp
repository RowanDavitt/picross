#include "loadingPage.h"
#include "helper/outlinedDraw.h"
#include "input/fileInput.h"

puzzleLoader::puzzleLoader(std::vector<std::vector<bool>> *puzzleDest) {
  fileList = std::vector<std::string>();
  puzzle = puzzleDest;
  listPzLnames(&fileList);
  makeOptionList();
  done = 0;
}

void puzzleLoader::makeOptionList() {
  float text_Y_increment = (GetScreenHeight() / (3 + fileList.size()));
  float text_X_size = GetScreenWidth() * BUTTON_X_SIZE_RATIO;
  float text_X_loc = (GetScreenWidth() - text_X_size) / 2;
  Vector2 pos = {text_X_loc, 2 * text_Y_increment};
  Vector2 size = {text_X_size, text_Y_increment};
  buttonListSize = fileList.size();

  for (size_t i = 0; i < buttonListSize; i++) {
    fileButtonList.emplace_back(pos, size, fileList[i], ElemCC::ColorVal::GRID_LINES);
    inputter.addRegion(&(fileButtonList.back()));
    pos.y += text_Y_increment;
  }
}

int puzzleLoader::LoadPageFrame() {
  if (IsWindowResized()) {
    resize();
  }
  // DrawText((std::to_string(temp)).c_str(), 10, 80, 20, WHITE);

  drawTitle();
  drawList();
  checkInputs();
  return done;
}

void puzzleLoader::drawList() {
  // for (size_t i = 0; i < buttonListSize; i++) {
  //   fileButtonList[i].draw();
  // }
  for (std::list<textButton>::iterator BlistIter = fileButtonList.begin(); BlistIter != fileButtonList.end(); ++BlistIter) {
    BlistIter->draw();
  }
}

void puzzleLoader::checkInputs() {

  inputter.checkClick();
  for (std::list<textButton>::iterator BlistIter = fileButtonList.begin(); BlistIter != fileButtonList.end(); ++BlistIter) {
    if (BlistIter->done) {
      readPuzzleFile(prefix + BlistIter->fileName, puzzle);
      done = 1;
      return;
    }
  }
}

void puzzleLoader::resize() {
  float text_Y_increment = (GetScreenHeight() / (3 + fileList.size()));
  float text_X_size = GetScreenWidth() * BUTTON_X_SIZE_RATIO;
  float text_X_loc = (GetScreenWidth() - text_X_size) / 2;
  Vector2 pos = {text_X_loc, 2 * text_Y_increment};
  Vector2 size = {text_X_size, text_Y_increment};

  for (std::list<textButton>::iterator BlistIter = fileButtonList.begin(); BlistIter != fileButtonList.end(); ++BlistIter) {
    BlistIter->resize(pos, size);
    pos.y += text_Y_increment;
  }
}

void puzzleLoader::drawTitle() {
  float text_Y_loc_increment = (GetScreenHeight() / (3 + fileList.size()));
  float text_X_loc = ((GetScreenWidth() - MeasureText(selectTitle.c_str(), text_Y_loc_increment / 2)) / 2) + 3;
  Vector2 textLoc = {text_X_loc, text_Y_loc_increment};
  DrawSuperText(selectTitle.c_str(), textLoc, 0, text_Y_loc_increment / 2, 3, ElemCC::LABEL_TEXT);
}

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
    fileButtonList.emplace_back(pos, size, removeplzExt(fileList[i]), ElemCC::ColorVal::GRID_LINES, ElemCC::ColorVal::LABEL_TEXT);
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
      readPuzzleFile(inputDirect + BlistIter->buttonText + puzzleExt, puzzle);
      done = 1;
      BlistIter->done = 0;
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
  Vector2 textboxSize = {(float)min(MeasureText(selectTitle.c_str(), text_Y_loc_increment), GetScreenWidth() * 0.75), text_Y_loc_increment};
  float text_X_loc = ((GetScreenWidth() - textboxSize.x) / 2);
  Vector2 textLoc = {text_X_loc, text_Y_loc_increment};
  drawBoxWithText(selectTitle.c_str(), textboxSize, textLoc, 0, 3, ElemCC::ColorVal::BACKGROUND_FILL, ElemCC::ColorVal::LABEL_TEXT);
}

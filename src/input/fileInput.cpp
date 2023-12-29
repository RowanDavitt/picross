#include "fileInput.h"
#include "dirent.h"

std::string inDir = "puzzles/";
std::string puzzleExt = ".pzl";

int listfilenames(std::string inputDir, std::vector<std::string> *outList, std::string extension) {
  struct dirent *ent;
  DIR *dir = opendir(inputDir.c_str());
  if (dir != NULL) {
    ent = readdir(dir);
    while (ent != NULL) {
      if (checkExt(std::string(ent->d_name), extension)) {
        outList->push_back(std::string(ent->d_name));
      }
      ent = readdir(dir);
    }
    closedir(dir);
    return EXIT_SUCCESS;
  } else {
    return EXIT_FAILURE;
  }
}

std::string listPzLnames() {
  std::vector<std::string> list;
  if (listfilenames(inDir, &list, puzzleExt)) {
    return "err";
  }
  if (!list.size()) {
    return "no";
  }
  return list[0];
}

bool checkExt(std::string file, std::string extension) {
  int end = file.size() - extension.size();
  if (end < 0) {
    return false;
  }
  for (unsigned int i = 0; i < extension.size(); i++) {
    if (file[end + i] != extension[i]) {
      return false;
    }
  }
  return true;
}

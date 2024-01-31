#include "fileInput.h"
#include "dirent.h"
#include <fstream>

std::string inputDirect1 = "puzzles/";
std::string puzzleExt1 = ".pzl";

int listfilenames(std::string inputDir, std::vector<std::string> *outList, std::string extension) {
  struct dirent *ent;
  DIR *dir = opendir(inputDir.c_str());
  if (dir != NULL) {

    while ((ent = readdir(dir)) != NULL) {
      std::string fileName = std::string(ent->d_name);
      if (checkExt(fileName, extension)) {
        (*outList).push_back(fileName);
      }
    }
    closedir(dir);
    return EXIT_SUCCESS;
  } else {
    return EXIT_FAILURE;
  }
}

std::string listPzLnames(std::vector<std::string> *outList) {
  if (listfilenames(inputDirect1, outList, puzzleExt1)) {
    return "err";
  }
  if (!(*outList).size()) {
    return "no";
  }
  return (*outList)[0];
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

std::string removeExt(std::string file, std::string extension) {
  int end = file.size() - extension.size();
  if (end < 0) {
    return file;
  }
  return file.substr(0, end);
}

std::string removeplzExt(std::string file) {

  return removeExt(file, puzzleExt1);
}

int readPuzzleFile(std::string filePath, std::vector<std::vector<bool>> *outPuzzle) {
  // open file
  std::ifstream targetFile(filePath);
  if (!targetFile) {
    return EXIT_FAILURE;
  }
  int column_num = 0;
  int row_num = 0;
  char enter;

  targetFile >> column_num;
  targetFile.ignore();
  targetFile >> row_num;
  targetFile.ignore();
  if (!column_num || !row_num) {
    return EXIT_FAILURE;
  }

  for (int row = 0; row < row_num; row++) {
    if ((*outPuzzle).size() <= ((unsigned int)row)) {
      (*outPuzzle).push_back(std::vector<bool>());
    }
    for (int col = 0; col < column_num; col++) {
      // write entry
      targetFile.get(enter);
      if (targetFile.eof()) {
        return EXIT_FAILURE;
      }
      if ((*outPuzzle)[row].size() <= ((unsigned int)col)) {
        (*outPuzzle)[row].push_back(atoi(&enter));
      } else {
        (*outPuzzle)[row][col] = atoi(&enter);
      }
    }
    // write "\n"
    targetFile.ignore();
    if (targetFile.eof()) {
      return EXIT_FAILURE;
    }
  }
  // close file
  targetFile.close();
  return EXIT_SUCCESS;
}

int writePuzzleFile(std::string filePath, std::vector<std::vector<bool>> *outPuzzle) {
  // open file
  std::ofstream targetFile(filePath);
  if (!targetFile) {
    return EXIT_FAILURE;
  }

  targetFile << std::to_string((*outPuzzle).size()) << "\n";
  targetFile << std::to_string((*outPuzzle)[0].size()) << "\n";

  for (std::vector<bool> column : (*outPuzzle)) {
    for (bool entry : column) {
      // write entry
      targetFile << std::to_string(entry);
    }
    // write "\n"
    targetFile << "\n";
  }
  // close file
  targetFile.close();
  return EXIT_SUCCESS;
}

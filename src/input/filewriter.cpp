#include "filewriter.h"
#include <fstream>
#include <iostream>

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
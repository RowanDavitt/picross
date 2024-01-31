#ifndef FILEIN
#define FILEIN
#include <string>
#include <vector>
int listfilenames(std::string, std::vector<std::string> *outList, std::string);
std::string listPzLnames(std::vector<std::string> *outList);

bool checkExt(std::string file, std::string extension);

int readPuzzleFile(std::string filePath, std::vector<std::vector<bool>> *outPuzzle);

int writePuzzleFile(std::string filePath, std::vector<std::vector<bool>> *outPuzzle);
std::string removeExt(std::string file, std::string extension);
std::string removeplzExt(std::string file);
#endif
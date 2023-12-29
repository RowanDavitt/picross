#include <string>
#include <vector>

#ifndef FILEIN
#define FILEIN

int listfilenames(std::string inDirect, std::vector<std::string> *outList, std::string extension);
std::string listPzLnames();

bool checkExt(std::string file, std::string extension);
#endif
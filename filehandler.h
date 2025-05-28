#ifndef FILEHANDLER_H
#define FILEHANDLER_H
#include "user.h"
#include <vector>

class FileHandler {
public:
  FileHandler();
  ~FileHandler();
  vector<vector<string>> readCsv(const string &filePath);
  void writeCsv(const string &filePath, const vector<vector<string>> &data);
};
#endif

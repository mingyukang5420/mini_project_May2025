// FileHandler.cpp
#include "FileHandler.h"
#include <algorithm> // For std::remove_if

std::vector<std::string> FileHandler::readCsvLine(std::istream &a_fileStream,
                                                  char a_delimiter) {
  std::vector<std::string> row;
  std::string cell;
  std::string line;

  if (std::getline(a_fileStream, line)) {
    std::stringstream lineStream(line);
    std::string currentCell;

    while (std::getline(lineStream, currentCell, a_delimiter)) {
      // Trim whitespace from the cell
      currentCell.erase(0, currentCell.find_first_not_of(" \t\n\r"));
      currentCell.erase(currentCell.find_last_not_of(" \t\n\r") + 1);
      row.push_back(currentCell);
    }
  }
  return row;
}

void FileHandler::writeCsvLine(std::ostream &a_fileStream,
                               const std::vector<std::string> &a_data,
                               char a_delimiter) {
  for (size_t i = 0; i < a_data.size(); ++i) {
    a_fileStream << a_data[i];
    if (i < a_data.size() - 1) {
      a_fileStream << a_delimiter;
    }
  }
  a_fileStream << std::endl;
}
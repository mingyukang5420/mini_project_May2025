// FileHandler.h
#pragma once
#include <fstream>
#include <string>
#include <vector>

class FileHandler {
public:
  std::vector<std::string> readLines(const std::string &filename) const {
    std::vector<std::string> lines;
    std::ifstream file(filename);
    std::string line;

    if (file.is_open()) {
      while (std::getline(file, line)) {
        if (!line.empty()) {
          lines.push_back(line);
        }
      }
      file.close();
    }

    return lines;
  }

  void writeLines(const std::string &filename,
                  const std::vector<std::string> &lines) const {
    std::ofstream file(filename);

    if (file.is_open()) {
      for (const auto &line : lines) {
        file << line << '\n';
      }
      file.close();
    }
  }
};
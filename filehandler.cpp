#include "filehandler.h"
#include <direct.h>
#include <fstream>
#include <sstream>

using namespace std;

bool FileHandler::isCacheValid(const string &filename) const {
  auto it = cache.find(filename);
  if (it == cache.end()) {
    return false;
  }

  auto now = chrono::system_clock::now();
  auto duration =
      chrono::duration_cast<chrono::minutes>(now - it->second.timestamp);
  return duration.count() < CACHE_TIMEOUT_MINUTES;
}

void FileHandler::updateCache(const string &filename, const string &content) {
  CacheEntry entry{content, chrono::system_clock::now()};
  cache[filename] = entry;
}

void FileHandler::setError(const string &error) { lastError = error; }

string FileHandler::readFile(const string &filename) {
  if (isCacheValid(filename)) {
    return cache[filename].content;
  }

  ifstream file(filename);
  if (!file.is_open()) {
    setError("파일을 열 수 없습니다: " + filename);
    return "";
  }

  stringstream buffer;
  buffer << file.rdbuf();
  string content = buffer.str();

  updateCache(filename, content);
  return content;
}

void FileHandler::writeFile(const string &filename, const string &content) {
  // 디렉토리 경로 추출
  size_t pos = filename.find_last_of("/\\");
  if (pos != string::npos) {
    string dir = filename.substr(0, pos);
    _mkdir(dir.c_str()); // Windows 전용 디렉토리 생성
  }

  ofstream file(filename);
  if (!file.is_open()) {
    setError("파일을 쓸 수 없습니다: " + filename);
    return;
  }

  file << content;
  updateCache(filename, content);
}

vector<vector<string>> FileHandler::readCSV(const string &filename) {
  vector<vector<string>> result;
  string content = readFile(filename);

  if (content.empty()) {
    return result;
  }

  stringstream ss(content);
  string line;

  while (getline(ss, line)) {
    vector<string> row;
    stringstream lineStream(line);
    string cell;

    while (getline(lineStream, cell, ',')) {
      if (!cell.empty() && cell.front() == '"' && cell.back() == '"') {
        cell = cell.substr(1, cell.length() - 2);
      }
      row.push_back(cell);
    }

    result.push_back(row);
  }

  return result;
}

bool FileHandler::writeCSV(const string &filename,
                           const vector<vector<string>> &data) {
  stringstream ss;

  for (const auto &row : data) {
    for (size_t i = 0; i < row.size(); ++i) {
      string cell = row[i];

      if (cell.find(',') != string::npos || cell.find('\n') != string::npos) {
        ss << '"' << cell << '"';
      } else {
        ss << cell;
      }

      if (i < row.size() - 1) {
        ss << ',';
      }
    }
    ss << '\n';
  }

  writeFile(filename, ss.str());
  return lastError.empty();
}

void FileHandler::clearCache() { cache.clear(); }

void FileHandler::invalidateCache(const string &filename) {
  cache.erase(filename);
}
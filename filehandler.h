#ifndef FILEHANDLER_H
#define FILEHANDLER_H

#include <chrono>
#include <map>
#include <string>
#include <vector>

using namespace std;

class FileHandler {
private:
  struct CacheEntry {
    string content;
    chrono::system_clock::time_point timestamp;
  };

  map<string, CacheEntry> cache;
  const int CACHE_TIMEOUT_MINUTES = 5;
  string lastError;

  bool isCacheValid(const string &filename) const;
  void updateCache(const string &filename, const string &content);
  void setError(const string &error);

public:
  FileHandler() = default;

  // 파일 읽기/쓰기 기본 함수
  string readFile(const string &filename);
  void writeFile(const string &filename, const string &content);

  // CSV 파일 처리
  vector<vector<string>> readCSV(const string &filename);
  bool writeCSV(const string &filename, const vector<vector<string>> &data);

  // 에러 처리
  string getLastError() const { return lastError; }
  void clearError() { lastError = ""; }

  // 캐시 관리
  void clearCache();
  void invalidateCache(const string &filename);
};

#endif

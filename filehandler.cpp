#include "filehandler.h"
#include <fstream>
#include <sstream>

using namespace std;

FileHandler::FileHandler() {}
FileHandler::~FileHandler() {}

vector<vector<string>> FileHandler::readCsv(const string &filePath) {
  vector<vector<string>> data;
  ifstream file(filePath); // 파일 열기
  string line;
  while (getline(file, line)) { // 파일 끝까지 반복
    vector<string> row;
    stringstream ss(line);
    string field;
    while (getline(ss, field, ',')) { // 쉼표 기준으로 문자열 분리
      row.push_back(field);           // 분리된 문자열을 벡터에 추가
    }
    data.push_back(row); // 분리된 문자열을 2d vector에 추가
  }
  return data; // 2d vector 반환
}

void FileHandler::writeCsv(const string &filePath,
                           const vector<vector<string>> &data) {
  ofstream file(filePath); // 파일 열기
  for (const auto &row : data) {
    for (const auto &field : row) {
      file << field << ","; // filestream에 field 데이터 쓰기
      // 벡터의 벡터 (2d vector)부터 출력
    }
    file << endl; // 1row 다 쓰면 줄바꿈
  }
  file.close(); // 파일 닫기
}

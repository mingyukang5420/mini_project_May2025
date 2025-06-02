// FileHandler.h
#ifndef __FILE_HANDLER_H__
#define __FILE_HANDLER_H__

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream> // For std::stringstream

class FileHandler {
public:
    // CSV 파일에서 한 줄을 읽어 문자열 벡터로 파싱하는 정적 메서드
    static std::vector<std::string> readCsvLine(std::istream& a_fileStream, char a_delimiter = ',');

    // CSV 파일에 한 줄을 쓰는 정적 메서드
    static void writeCsvLine(std::ostream& a_fileStream, const std::vector<std::string>& a_data, char a_delimiter = ',');

private:
    FileHandler() = delete; // 정적 클래스로서 인스턴스화를 막음
    ~FileHandler() = delete;
};

#endif // __FILE_HANDLER_H__
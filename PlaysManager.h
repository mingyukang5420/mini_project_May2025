// PlaysManager.h
#pragma once

#include "Manager.h"
#include "Plays.h"
#include <ctime> // For time_t
#include <map>
#include <string>
#include <vector>

class PlaysManager : public Manager<Plays> {
public:
  PlaysManager();
  virtual ~PlaysManager();

  void add(const Plays &play) override;        // 연극 추가
  void input() override;                       // 사용자 입력으로 연극 추가
  bool remove(const std::string &id) override; // 연극 삭제
  bool modify(const std::string &id) override; // 연극 정보 수정
  Plays *search(const std::string &id) const override; // 연극 조회
  std::vector<Plays> getAll() const override;          // 모든 연극 정보 반환
  std::string makeId() const override;                 // ID 생성

  void loadFromFile(const std::string &filename);
  void saveToFile(const std::string &filename) const;

private:
  std::map<std::string, Plays *> m_playList;
  const std::string M_PLAYS_FILE_NAME = "playslist.csv";
  std::string generateId() const;

  // 날짜 변환 유틸리티 함수
  time_t parseDate(const std::string &dateString);
  std::string formatDate(time_t time);
};
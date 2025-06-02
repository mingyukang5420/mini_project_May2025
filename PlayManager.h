// PlayManager.h
#ifndef __PLAY_MANAGER_H__
#define __PLAY_MANAGER_H__

#include "Play.h"
#include <ctime> // For time_t
#include <map>
#include <memory> // For std::unique_ptr
#include <string>
#include <vector>

class PlayManager {
public:
  PlayManager();
  ~PlayManager();

  void addPlay(const Play &a_play);      // 연극 추가 (ID 자동 생성)
  void inputPlay();                      // 사용자 입력으로 연극 추가
  bool deletePlay(int a_playsId);        // 연극 삭제
  bool modifyPlay(int a_playsId);        // 연극 정보 수정
  Play *searchPlay(int a_playsId);       // 연극 조회 (포인터 반환)
  std::vector<Play> getAllPlays() const; // 모든 연극 정보 반환

private:
  std::map<int, std::unique_ptr<Play>> m_playList;
  const std::string M_PLAYS_FILE_NAME = "playslist.csv";

  void loadPlaysFromFile(); // 파일에서 연극 정보 로드
  void savePlaysToFile();   // 파일에 연극 정보 저장
  int makePlayId();         // 새로운 연극 ID 생성

  // YYYY-MM-DD 문자열을 time_t로 변환
  time_t parseDate(const std::string &a_dateString);
  // time_t를 YYYY-MM-DD 문자열로 변환
  std::string formatDate(time_t a_time);
};

#endif // __PLAY_MANAGER_H__
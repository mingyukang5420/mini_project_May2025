#ifndef PLAYSMANAGER_H
#define PLAYSMANAGER_H

#include "filehandler.h"
#include "plays.h"
#include "user.h"
#include <functional>
#include <map>
#include <string>
#include <vector>

class PlaysManager {
public:
  PlaysManager();
  ~PlaysManager();

  // 기본 공연 관리
  bool addPlays(const Plays &play, const User *requester);
  bool removePlays(int playId, const User *requester);
  bool modifyPlays(int playId, const Plays &updatedPlay, const User *requester);
  void viewPlays() const;
  Plays *searchPlays(int playId) const;

  // 고급 검색 기능
  vector<Plays *> getAllPlays() const;
  vector<Plays *> searchPlaysByName(const string &name) const;
  vector<Plays *> searchPlaysByGenre(const string &genre) const;
  vector<Plays *> searchPlaysByDate(const string &date) const;
  vector<Plays *> searchPlaysByPriceRange(int minPrice, int maxPrice) const;
  vector<Plays *> searchPlaysByLocation(const string &location) const;
  vector<Plays *> searchPlaysByCast(const string &castMember) const;

  // 공연 상태 관리
  bool setPlayStatus(int playId, const string &status, const User *requester);
  bool updateReviewScore(int playId, float newScore);
  bool updateCast(int playId, const vector<string> &newCast,
                  const User *requester);
  bool updatePrice(int playId, int newPrice, const User *requester);

  // 통계 및 분석
  int getTotalPlaysCount() const;
  float getAverageTicketPrice() const;
  map<string, int> getPlaysByGenre() const;    // <genre, count>
  map<string, int> getPlaysByLocation() const; // <location, count>
  vector<Plays *> getTopRatedPlays(int limit) const;
  vector<Plays *> getUpcomingPlays() const; // 현재 날짜 이후의 공연들

  // 유효성 검사
  bool isValidPlayId(int playId) const;
  bool hasScheduleConflict(const Plays &play) const;
  bool isValidPrice(int price) const;
  bool isValidDate(time_t date) const;

private:
  map<int, Plays *> playsList;
  FileHandler fileHandler;

  // 유틸리티 함수
  int makePlaysId() const;
  bool saveToDatabase();
  bool loadFromDatabase();

  // 내부 헬퍼 함수
  vector<Plays *>
  filterPlays(const function<bool(const Plays *)> &predicate) const;
  bool hasPermission(const User *requester) const;
  bool validatePlay(const Plays &play) const;
};

#endif // PLAYSMANAGER_H

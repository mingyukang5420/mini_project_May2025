#include "playsmanager.h"
#include <algorithm>
#include <ctime>
#include <iomanip>
#include <iostream>
#include <sstream>

using namespace std;

PlaysManager::PlaysManager() { loadFromDatabase(); }

PlaysManager::~PlaysManager() {
  saveToDatabase();
  for (auto &pair : playsList) {
    delete pair.second;
  }
  playsList.clear();
}

bool PlaysManager::addPlays(const Plays &play, const User *requester) {
  if (!hasPermission(requester)) {
    cout << "권한이 없습니다." << endl;
    return false;
  }

  if (!validatePlay(play)) {
    cout << "유효하지 않은 공연 정보입니다." << endl;
    return false;
  }

  if (hasScheduleConflict(play)) {
    cout << "해당 시간에 이미 다른 공연이 예정되어 있습니다." << endl;
    return false;
  }

  try {
    int playId = makePlaysId();
    Plays *newPlay = new Plays(play); // 복사 생성자 사용
    playsList[playId] = newPlay;
    return saveToDatabase();
  } catch (const exception &e) {
    cout << "공연 추가 중 오류 발생: " << e.what() << endl;
    return false;
  }
}

bool PlaysManager::removePlays(int playId, const User *requester) {
  if (!hasPermission(requester)) {
    cout << "권한이 없습니다." << endl;
    return false;
  }

  auto it = playsList.find(playId);
  if (it == playsList.end()) {
    cout << "공연을 찾을 수 없습니다." << endl;
    return false;
  }

  delete it->second;
  playsList.erase(it);
  return saveToDatabase();
}

bool PlaysManager::modifyPlays(int playId, const Plays &updatedPlay,
                               const User *requester) {
  if (!hasPermission(requester)) {
    cout << "권한이 없습니다." << endl;
    return false;
  }

  auto it = playsList.find(playId);
  if (it == playsList.end()) {
    cout << "공연을 찾을 수 없습니다." << endl;
    return false;
  }

  if (!validatePlay(updatedPlay)) {
    cout << "유효하지 않은 공연 정보입니다." << endl;
    return false;
  }

  if (hasScheduleConflict(updatedPlay)) {
    cout << "해당 시간에 이미 다른 공연이 예정되어 있습니다." << endl;
    return false;
  }

  *(it->second) = updatedPlay; // 복사 대입 연산자 사용
  return saveToDatabase();
}

void PlaysManager::viewPlays() const {
  cout << "\n=== 공연 목록 ===" << endl;
  if (playsList.empty()) {
    cout << "등록된 공연이 없습니다." << endl;
    return;
  }

  for (const auto &pair : playsList) {
    const Plays *play = pair.second;
    cout << "공연 ID: " << play->getPlaysId() << endl;
    cout << "제목: " << play->getName() << endl;
    cout << "장소: " << play->getLocation() << endl;
    cout << "날짜: " << play->getDate() << endl;
    cout << "시간: " << play->getTime() << endl;
    cout << "가격: " << play->getPrice() << endl;
    cout << "장르: " << play->getGenre() << endl;
    cout << "평점: " << play->getReviewScore() << endl;
    cout << "출연진: ";
    for (const auto &cast : play->getCast()) {
      cout << cast << ", ";
    }
    cout << "\n상영시간: " << play->getRunningTime() << "분" << endl;
    cout << "---------------" << endl;
  }
}

Plays *PlaysManager::searchPlays(int playId) const {
  auto it = playsList.find(playId);
  return (it != playsList.end()) ? it->second : nullptr;
}

vector<Plays *> PlaysManager::getAllPlays() const {
  vector<Plays *> result;
  result.reserve(playsList.size());
  for (const auto &pair : playsList) {
    result.push_back(pair.second);
  }
  return result;
}

vector<Plays *> PlaysManager::filterPlays(
    const function<bool(const Plays *)> &predicate) const {
  vector<Plays *> result;
  for (const auto &pair : playsList) {
    if (predicate(pair.second)) {
      result.push_back(pair.second);
    }
  }
  return result;
}

vector<Plays *> PlaysManager::searchPlaysByName(const string &name) const {
  return filterPlays([&name](const Plays *p) {
    return p->getName().find(name) != string::npos;
  });
}

vector<Plays *> PlaysManager::searchPlaysByGenre(const string &genre) const {
  return filterPlays(
      [&genre](const Plays *p) { return p->getGenre() == genre; });
}

vector<Plays *> PlaysManager::searchPlaysByDate(const string &date) const {
  return filterPlays([&date](const Plays *p) {
    return p->getDate().find(date) != string::npos;
  });
}

vector<Plays *> PlaysManager::searchPlaysByPriceRange(int minPrice,
                                                      int maxPrice) const {
  return filterPlays([minPrice, maxPrice](const Plays *p) {
    int price = p->getPrice();
    return price >= minPrice && price <= maxPrice;
  });
}

vector<Plays *>
PlaysManager::searchPlaysByLocation(const string &location) const {
  return filterPlays([&location](const Plays *p) {
    return p->getLocation().find(location) != string::npos;
  });
}

vector<Plays *>
PlaysManager::searchPlaysByCast(const string &castMember) const {
  return filterPlays([&castMember](const Plays *p) {
    const auto &cast = p->getCast();
    return find_if(cast.begin(), cast.end(),
                   [&castMember](const string &member) {
                     return member.find(castMember) != string::npos;
                   }) != cast.end();
  });
}

bool PlaysManager::setPlayStatus(int playId, const string &status,
                                 const User *requester) {
  if (!hasPermission(requester)) {
    cout << "권한이 없습니다." << endl;
    return false;
  }

  auto it = playsList.find(playId);
  if (it == playsList.end())
    return false;

  if (status != "예정" && status != "진행중" && status != "종료") {
    cout << "유효하지 않은 상태입니다." << endl;
    return false;
  }

  it->second->setStatus(status);
  return saveToDatabase();
}

bool PlaysManager::updateReviewScore(int playId, float newScore) {
  if (newScore < 0.0f || newScore > 5.0f) {
    cout << "유효하지 않은 평점입니다." << endl;
    return false;
  }

  auto it = playsList.find(playId);
  if (it == playsList.end())
    return false;

  it->second->setReviewScore(newScore);
  return saveToDatabase();
}

bool PlaysManager::updateCast(int playId, const vector<string> &newCast,
                              const User *requester) {
  if (!hasPermission(requester)) {
    cout << "권한이 없습니다." << endl;
    return false;
  }

  if (newCast.empty()) {
    cout << "출연진 목록이 비어있습니다." << endl;
    return false;
  }

  auto it = playsList.find(playId);
  if (it == playsList.end())
    return false;

  it->second->setCast(newCast);
  return saveToDatabase();
}

bool PlaysManager::updatePrice(int playId, int newPrice,
                               const User *requester) {
  if (!hasPermission(requester)) {
    cout << "권한이 없습니다." << endl;
    return false;
  }

  if (!isValidPrice(newPrice)) {
    cout << "유효하지 않은 가격입니다." << endl;
    return false;
  }

  auto it = playsList.find(playId);
  if (it == playsList.end())
    return false;

  it->second->setPrice(newPrice);
  return saveToDatabase();
}

int PlaysManager::getTotalPlaysCount() const { return playsList.size(); }

float PlaysManager::getAverageTicketPrice() const {
  if (playsList.empty())
    return 0.0f;

  float total = 0.0f;
  for (const auto &pair : playsList) {
    total += pair.second->getPrice();
  }
  return total / playsList.size();
}

map<string, int> PlaysManager::getPlaysByGenre() const {
  map<string, int> genreCount;
  for (const auto &pair : playsList) {
    genreCount[pair.second->getGenre()]++;
  }
  return genreCount;
}

map<string, int> PlaysManager::getPlaysByLocation() const {
  map<string, int> locationCount;
  for (const auto &pair : playsList) {
    locationCount[pair.second->getLocation()]++;
  }
  return locationCount;
}

vector<Plays *> PlaysManager::getTopRatedPlays(int limit) const {
  vector<Plays *> plays = getAllPlays();
  sort(plays.begin(), plays.end(), [](const Plays *a, const Plays *b) {
    return a->getReviewScore() > b->getReviewScore();
  });

  if (static_cast<size_t>(limit) < plays.size()) {
    plays.resize(limit);
  }
  return plays;
}

vector<Plays *> PlaysManager::getUpcomingPlays() const {
  return filterPlays([](const Plays *p) { return p->isUpcoming(); });
}

bool PlaysManager::isValidPlayId(int playId) const {
  return playsList.find(playId) != playsList.end();
}

bool PlaysManager::hasScheduleConflict(const Plays &play) const {
  for (const auto &pair : playsList) {
    if (pair.second->hasTimeConflict(play)) {
      return true;
    }
  }
  return false;
}

bool PlaysManager::isValidPrice(int price) const {
  return price >= 0 && price <= 1000000; // 임의의 상한가 설정
}

bool PlaysManager::isValidDate(time_t date) const {
  time_t now = time(nullptr);
  return date > now; // 현재 시간 이후만 유효
}

int PlaysManager::makePlaysId() const {
  int maxId = 0;
  for (const auto &pair : playsList) {
    if (pair.first > maxId) {
      maxId = pair.first;
    }
  }
  return maxId + 1;
}

bool PlaysManager::saveToDatabase() {
  try {
    vector<vector<string>> data;
    data.push_back({"PlayID", "Name", "Location", "Date", "Time", "Price",
                    "Genre", "ReviewScore", "Cast", "RunningTime"});

    for (const auto &pair : playsList) {
      const Plays *play = pair.second;
      vector<string> row;

      row.push_back(to_string(play->getPlaysId()));
      row.push_back(play->getName());
      row.push_back(play->getLocation());
      row.push_back(play->getDate());
      row.push_back(play->getTime());
      row.push_back(to_string(play->getPrice()));
      row.push_back(play->getGenre());
      row.push_back(to_string(play->getReviewScore()));

      string cast;
      const auto &castList = play->getCast();
      for (size_t i = 0; i < castList.size(); i++) {
        cast += castList[i];
        if (i < castList.size() - 1) {
          cast += ";";
        }
      }
      row.push_back(cast);
      row.push_back(to_string(play->getRunningTime()));
      data.push_back(row);
    }

    return fileHandler.writeCsv("plays.csv", data);
  } catch (const exception &e) {
    cout << "파일 저장 중 오류 발생: " << e.what() << endl;
    return false;
  }
}

bool PlaysManager::loadFromDatabase() {
  try {
    if (!fileHandler.exists("plays.csv")) {
      // 초기 빈 파일 생성
      vector<vector<string>> headers = {{"PlayID", "Name", "Location", "Date",
                                         "Time", "Price", "Genre",
                                         "ReviewScore", "Cast", "RunningTime"}};
      return fileHandler.writeCsv("plays.csv", headers);
    }

    vector<vector<string>> data = fileHandler.readCsv("plays.csv");

    for (auto &pair : playsList) {
      delete pair.second;
    }
    playsList.clear();

    for (size_t i = 1; i < data.size(); i++) {
      const vector<string> &row = data[i];
      if (row.size() >= 10) {
        Plays *play = new Plays();

        play->setId(stoi(row[0]));
        play->setName(row[1]);
        play->setLocation(row[2]);

        struct tm timeinfo = {};
        istringstream dateStream(row[3] + " " + row[4]);
        dateStream >> get_time(&timeinfo, "%Y-%m-%d %H:%M");

        play->setDate(mktime(&timeinfo));
        play->setTime(mktime(&timeinfo));

        play->setPrice(stoi(row[5]));
        play->setGenre(row[6]);
        play->setReviewScore(stof(row[7]));

        vector<string> cast;
        istringstream castStream(row[8]);
        string castMember;
        while (getline(castStream, castMember, ';')) {
          cast.push_back(castMember);
        }
        play->setCast(cast);

        play->setRunningTime(stoi(row[9]));

        playsList[play->getPlaysId()] = play;
      }
    }

    return true;
  } catch (const exception &e) {
    cout << "파일 로드 중 오류 발생: " << e.what() << endl;
    return false;
  }
}

bool PlaysManager::hasPermission(const User *requester) const {
  return requester && requester->getUserType() == "admin";
}

bool PlaysManager::validatePlay(const Plays &play) const {
  // 기본적인 유효성 검사
  if (play.getName().empty() || play.getLocation().empty() ||
      play.getGenre().empty() || play.getCast().empty() ||
      play.getRunningTime() <= 0 || !isValidPrice(play.getPrice()) ||
      !isValidDate(play.getRawDate())) {
    return false;
  }
  return true;
}

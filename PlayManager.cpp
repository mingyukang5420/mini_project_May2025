// PlayManager.cpp
#include "PlayManager.h"
#include "DisplayConsoleView.h"
#include "FileHandler.h"
#include <algorithm>
#include <fstream>
#include <iomanip> // For std::put_time, std::get_time
#include <limits>
#include <sstream>

PlayManager::PlayManager() { loadPlaysFromFile(); }

PlayManager::~PlayManager() { savePlaysToFile(); }

time_t PlayManager::parseDate(const std::string &a_dateString) {
  std::tm t = {};
  std::istringstream ss(a_dateString);
  ss >> std::get_time(&t, "%Y-%m-%d");
  if (ss.fail()) {
    DisplayConsoleView::showErrorMessage("날짜 파싱 실패: " + a_dateString);
    return 0; // 유효하지 않은 날짜일 경우 0 반환
  }
  return std::mktime(&t);
}

std::string PlayManager::formatDate(time_t a_time) {
  std::tm *ptm = std::localtime(&a_time);
  std::ostringstream ss;
  ss << std::put_time(ptm, "%Y-%m-%d");
  return ss.str();
}

void PlayManager::loadPlaysFromFile() {
  std::ifstream file(M_PLAYS_FILE_NAME);
  if (!file.is_open()) {
    return;
  }

  while (!file.eof()) {
    std::vector<std::string> row = FileHandler::readCsvLine(file);
    if (row.empty())
      continue;

    if (row.size() < 5) {
      DisplayConsoleView::showErrorMessage(
          "playslist.csv 파일에서 유효하지 않은 데이터 형식을 발견했습니다. 이 "
          "줄은 건너뜁니다.");
      continue;
    }

    try {
      int id = std::stoi(row[0]);
      std::string name = row[1];
      time_t showingDate = parseDate(row[2]);
      std::string genre = row[3];
      float price = std::stof(row[4]);
      m_playList.insert(
          {id, std::make_unique<Play>(id, name, showingDate, genre, price)});
    } catch (const std::exception &e) {
      DisplayConsoleView::showErrorMessage(
          "playslist.csv 파일을 파싱하는 중 오류가 발생했습니다: " +
          std::string(e.what()));
    }
  }
  file.close();
}

void PlayManager::savePlaysToFile() {
  std::ofstream file(M_PLAYS_FILE_NAME);
  if (!file.is_open()) {
    DisplayConsoleView::showErrorMessage(
        "playslist.csv 파일을 저장할 수 없습니다.");
    return;
  }

  for (const auto &pair : m_playList) {
    const Play *play = pair.second.get();
    std::vector<std::string> data;
    data.push_back(std::to_string(play->getPlaysId()));
    data.push_back(play->getPlaysName());
    data.push_back(
        formatDate(play->getShowingDate())); // time_t를 문자열로 변환하여 저장
    data.push_back(play->getGenre());
    data.push_back(std::to_string(play->getPrice()));
    FileHandler::writeCsvLine(file, data);
  }
  file.close();
}

int PlayManager::makePlayId() {
  if (m_playList.empty()) {
    return 1;
  } else {
    int maxId = 0;
    for (const auto &pair : m_playList) {
      if (pair.first > maxId) {
        maxId = pair.first;
      }
    }
    return maxId + 1;
  }
}

void PlayManager::addPlay(const Play &a_play) {
  m_playList.insert({a_play.getPlaysId(), std::make_unique<Play>(a_play)});
  savePlaysToFile();
  DisplayConsoleView::showMessage("연극 정보가 추가되었습니다.");
}

void PlayManager::inputPlay() {
  std::string name, dateStr, genre;
  float price;

  std::cout << "연극 제목 : ";
  std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
  std::getline(std::cin, name);

  std::cout << "상영일 (YYYY-MM-DD) : ";
  std::getline(std::cin, dateStr);
  time_t showingDate = parseDate(dateStr);
  if (showingDate == 0) { // 날짜 파싱 실패
    DisplayConsoleView::showErrorMessage(
        "유효하지 않은 날짜 형식입니다. 연극 추가를 취소합니다.");
    return;
  }

  std::cout << "장르 : ";
  std::getline(std::cin, genre);

  std::cout << "가격 : ";
  // float 입력 후 버퍼 비우기
  while (!(std::cin >> price)) {
    DisplayConsoleView::showErrorMessage(
        "유효하지 않은 가격입니다. 숫자를 입력해주세요.");
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cout << "가격 : ";
  }
  std::cin.ignore(std::numeric_limits<std::streamsize>::max(),
                  '\n'); // float 입력 후 남은 개행문자 처리

  int id = makePlayId();
  m_playList.insert(
      {id, std::make_unique<Play>(id, name, showingDate, genre, price)});
  savePlaysToFile();
  DisplayConsoleView::showMessage("새로운 연극이 등록되었습니다. ID: " +
                                  std::to_string(id));
}

bool PlayManager::deletePlay(int a_playsId) {
  auto it = m_playList.find(a_playsId);
  if (it != m_playList.end()) {
    m_playList.erase(it);
    savePlaysToFile();
    DisplayConsoleView::showMessage("연극 ID " + std::to_string(a_playsId) +
                                    "가 삭제되었습니다.");
    return true;
  } else {
    DisplayConsoleView::showErrorMessage(
        "연극 ID " + std::to_string(a_playsId) + "를 찾을 수 없습니다.");
    return false;
  }
}

bool PlayManager::modifyPlay(int a_playsId) {
  Play *play = searchPlay(a_playsId);
  if (play) {
    DisplayConsoleView::showMessage("현재 연극 정보:");
    DisplayConsoleView::displayPlay(play);

    std::string newName, newDateStr, newGenre;
    float newPrice;
    // bool priceChanged = false;

    std::cout << "새로운 연극 제목 (현재: " << play->getPlaysName() << ") : ";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::getline(std::cin, newName);
    if (!newName.empty()) {
      play->setPlaysName(newName);
    }

    std::cout << "새로운 상영일 (YYYY-MM-DD, 현재: "
              << formatDate(play->getShowingDate()) << ") : ";
    std::getline(std::cin, newDateStr);
    if (!newDateStr.empty()) {
      time_t newShowingDate = parseDate(newDateStr);
      if (newShowingDate != 0) {
        play->setShowingDate(newShowingDate);
      } else {
        DisplayConsoleView::showErrorMessage(
            "유효하지 않은 날짜 형식입니다. 상영일 변경을 취소합니다.");
      }
    }

    std::cout << "새로운 장르 (현재: " << play->getGenre() << ") : ";
    std::getline(std::cin, newGenre);
    if (!newGenre.empty()) {
      play->setGenre(newGenre);
    }

    std::cout << "새로운 가격 (현재: " << std::fixed << std::setprecision(2)
              << play->getPrice() << ") : ";
    std::string priceInput;
    std::getline(std::cin, priceInput); // 전체 라인을 읽고
    if (!priceInput.empty()) {
      std::stringstream ss(priceInput);
      if (ss >> newPrice) { // 스트림에서 float으로 파싱 시도
        play->setPrice(newPrice);
        // priceChanged = true;
      } else {
        DisplayConsoleView::showErrorMessage(
            "유효하지 않은 가격 형식입니다. 가격 변경을 취소합니다.");
      }
    }

    savePlaysToFile();
    DisplayConsoleView::showMessage("연극 정보가 수정되었습니다.");
    return true;
  } else {
    DisplayConsoleView::showErrorMessage(
        "연극 ID " + std::to_string(a_playsId) + "를 찾을 수 없습니다.");
    return false;
  }
}

Play *PlayManager::searchPlay(int a_playsId) {
  auto it = m_playList.find(a_playsId);
  if (it != m_playList.end()) {
    return it->second.get();
  }
  return nullptr;
}

std::vector<Play> PlayManager::getAllPlays() const {
  std::vector<Play> plays;
  for (const auto &pair : m_playList) {
    plays.push_back(*(pair.second));
  }
  return plays;
}
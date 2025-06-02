// PlaysManager.cpp
#include "PlaysManager.h"
#include "DisplayConsoleView.h"
#include <fstream>
#include <iomanip>
#include <random>
#include <sstream>

PlaysManager::PlaysManager() { loadFromFile(M_PLAYS_FILE_NAME); }

PlaysManager::~PlaysManager() {
  saveToFile(M_PLAYS_FILE_NAME);
  for (auto &pair : m_playList) {
    delete pair.second;
  }
}

void PlaysManager::add(const Plays &play) {
  Plays newPlay = play;
  newPlay.setId(generateId());
  Manager<Plays>::add(newPlay);
}

void PlaysManager::input() {
  std::string title = DisplayConsoleView::getInput("공연 제목: ");
  std::string date = DisplayConsoleView::getInput("공연 날짜: ");
  add(Plays(title, date));
  DisplayConsoleView::showMessage("공연이 등록되었습니다.");
}

bool PlaysManager::remove(const std::string &id) {
  auto it = m_playList.find(id);
  if (it != m_playList.end()) {
    delete it->second;
    m_playList.erase(it);
    saveToFile(M_PLAYS_FILE_NAME);
    DisplayConsoleView::showMessage("Play ID " + id + " has been deleted.");
    return true;
  }
  DisplayConsoleView::showErrorMessage("Play ID " + id + " not found.");
  return false;
}

bool PlaysManager::modify(const std::string &id) {
  Plays *play = search(id);
  if (play) {
    std::string title = DisplayConsoleView::getInput("새 제목: ");
    std::string date = DisplayConsoleView::getInput("새 날짜: ");
    if (!title.empty())
      play->setTitle(title);
    if (!date.empty())
      play->setDate(date);
    DisplayConsoleView::showMessage("공연 정보가 수정되었습니다.");
    return true;
  }
  DisplayConsoleView::showErrorMessage("공연을 찾을 수 없습니다.");
  return false;
}

Plays *PlaysManager::search(const std::string &id) const {
  auto it = m_playList.find(id);
  return (it != m_playList.end()) ? it->second : nullptr;
}

std::vector<Plays> PlaysManager::getAll() const {
  std::vector<Plays> plays;
  for (const auto &pair : m_playList) {
    plays.push_back(*pair.second);
  }
  return plays;
}

void PlaysManager::loadFromFile(const std::string &filename) {
  std::ifstream file(filename);
  if (!file.is_open())
    return;

  std::string line;
  while (std::getline(file, line)) {
    std::stringstream ss(line);
    std::string id, title, date;
    std::getline(ss, id, ',');
    std::getline(ss, title, ',');
    std::getline(ss, date, ',');

    if (!id.empty() && !title.empty()) {
      m_playList[id] = new Plays(id, title, date);
    }
  }
  file.close();
}

void PlaysManager::saveToFile(const std::string &filename) const {
  std::ofstream file(filename);
  if (!file.is_open()) {
    DisplayConsoleView::showErrorMessage("Cannot save to " + filename);
    return;
  }

  for (const auto &pair : m_playList) {
    const Plays *play = pair.second;
    file << play->getId() << "," << play->getTitle() << "," << play->getDate()
         << "\n";
  }
  file.close();
}

std::string PlaysManager::makeId() const { return generateId(); }

time_t PlaysManager::parseDate(const std::string &dateString) {
  std::tm tm = {};
  std::istringstream ss(dateString);
  ss >> std::get_time(&tm, "%Y-%m-%d");
  if (ss.fail()) {
    throw std::runtime_error("Invalid date format. Use YYYY-MM-DD");
  }
  return std::mktime(&tm);
}

std::string PlaysManager::formatDate(time_t time) {
  char buffer[11];
  std::strftime(buffer, sizeof(buffer), "%Y-%m-%d", std::localtime(&time));
  return std::string(buffer);
}

std::string PlaysManager::generateId() const {
  static std::random_device rd;
  static std::mt19937 gen(rd());
  static std::uniform_int_distribution<> dis(10000, 99999);

  std::string id;
  do {
    id = "P" + std::to_string(dis(gen));
  } while (search(id) != nullptr);

  return id;
}
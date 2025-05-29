#include "plays.h"
#include <ctime>
#include <iomanip>
#include <sstream>

Plays::Plays() {}
Plays::~Plays() {}

string Plays::getDate() const {
  char buffer[26];
  struct tm *timeinfo = localtime(&m_playsDate);
  strftime(buffer, 26, "%Y-%m-%d", timeinfo);
  return string(buffer);
}

string Plays::getTime() const {
  char buffer[26];
  struct tm *timeinfo = localtime(&m_playsTime);
  strftime(buffer, 26, "%H:%M", timeinfo);
  return string(buffer);
}
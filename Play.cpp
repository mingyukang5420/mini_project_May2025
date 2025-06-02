// Play.cpp
#include "Play.h"

Play::Play(int a_id, std::string a_name, time_t a_showingDate,
           std::string a_genre, float a_price)
    : m_playsId(a_id), m_playsName(a_name), m_showingDate(a_showingDate),
      m_genre(a_genre), m_price(a_price) {}

int Play::getPlaysId() const { return m_playsId; }

std::string Play::getPlaysName() const { return m_playsName; }

time_t Play::getShowingDate() const { return m_showingDate; }

std::string Play::getGenre() const { return m_genre; }

float Play::getPrice() const { return m_price; }

void Play::setPlaysName(const std::string &a_name) { m_playsName = a_name; }

void Play::setShowingDate(time_t a_showingDate) {
  m_showingDate = a_showingDate;
}

void Play::setGenre(const std::string &a_genre) { m_genre = a_genre; }

void Play::setPrice(float a_price) { m_price = a_price; }
// Plays.h
#pragma once
#include <string>

class Plays {
public:
  Plays(const std::string &title = "", const std::string &date = "")
      : m_id(""), m_title(title), m_date(date) {}

  Plays(const std::string &id, const std::string &title,
        const std::string &date)
      : m_id(id), m_title(title), m_date(date) {}

  const std::string &getId() const { return m_id; }
  const std::string &getTitle() const { return m_title; }
  const std::string &getDate() const { return m_date; }

  void setId(const std::string &id) { m_id = id; }
  void setTitle(const std::string &title) { m_title = title; }
  void setDate(const std::string &date) { m_date = date; }

private:
  std::string m_id;
  std::string m_title;
  std::string m_date;
};
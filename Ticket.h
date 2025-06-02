// Ticket.h
#pragma once
#include <string>

class Ticket {
public:
  Ticket(const std::string &customerId, const std::string &playId)
      : m_customerId(customerId), m_playId(playId) {}

  const std::string &getCustomerId() const { return m_customerId; }
  const std::string &getPlayId() const { return m_playId; }
  const std::string &getId() const { return m_customerId; }

  void setCustomerId(const std::string &customerId) {
    m_customerId = customerId;
  }
  void setPlayId(const std::string &playId) { m_playId = playId; }

private:
  std::string m_customerId;
  std::string m_playId;
};
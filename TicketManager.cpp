// TicketManager.cpp
#include "TicketManager.h"
#include "DisplayConsoleView.h"
#include "FileHandler.h"
#include <random>
#include <sstream>

TicketManager::TicketManager() { loadFromFile(M_TICKET_FILE_NAME); }

TicketManager::~TicketManager() {
  saveToFile(M_TICKET_FILE_NAME);
  for (auto &pair : m_ticketList) {
    delete pair.second;
  }
}

void TicketManager::add(const Ticket &ticket) { Manager<Ticket>::add(ticket); }

void TicketManager::input() {
  std::string customerId = DisplayConsoleView::getInput("고객 ID: ");
  std::string playId = DisplayConsoleView::getInput("공연 ID: ");
  if (add(customerId, playId)) {
    DisplayConsoleView::showMessage("예매가 완료되었습니다.");
  } else {
    DisplayConsoleView::showErrorMessage("예매에 실패했습니다.");
  }
}

bool TicketManager::modify(const std::string &id) {
  Ticket *ticket = search(id);
  if (ticket) {
    std::string customerId = DisplayConsoleView::getInput("새 고객 ID: ");
    std::string playId = DisplayConsoleView::getInput("새 공연 ID: ");
    if (!customerId.empty())
      ticket->setCustomerId(customerId);
    if (!playId.empty())
      ticket->setPlayId(playId);
    DisplayConsoleView::showMessage("예매 정보가 수정되었습니다.");
    return true;
  }
  DisplayConsoleView::showErrorMessage("예매를 찾을 수 없습니다.");
  return false;
}

bool TicketManager::add(const std::string &customerId,
                        const std::string &playId) {
  Ticket ticket(customerId, playId);
  Manager<Ticket>::add(ticket);
  return true;
}

bool TicketManager::remove(const std::string &id) {
  auto it = m_ticketList.find(id);
  if (it != m_ticketList.end()) {
    delete it->second;
    m_ticketList.erase(it);
    saveToFile(M_TICKET_FILE_NAME);
    return true;
  }
  return false;
}

bool TicketManager::remove(const std::string &customerId,
                           const std::string &playId) {
  auto it = std::find_if(m_items.begin(), m_items.end(), [&](const Ticket &t) {
    return t.getCustomerId() == customerId && t.getPlayId() == playId;
  });
  if (it != m_items.end()) {
    m_items.erase(it);
    return true;
  }
  return false;
}

std::vector<Ticket>
TicketManager::getCustomerTickets(const std::string &customerId) const {
  std::vector<Ticket> tickets;
  for (const auto &pair : m_ticketList) {
    if (pair.second->getCustomerId() == customerId) {
      tickets.push_back(*pair.second);
    }
  }
  return tickets;
}

std::vector<Ticket>
TicketManager::getPlayTickets(const std::string &playsId) const {
  std::vector<Ticket> tickets;
  for (const auto &pair : m_ticketList) {
    if (pair.second->getPlayId() == playsId) {
      tickets.push_back(*pair.second);
    }
  }
  return tickets;
}

void TicketManager::loadFromFile(const std::string &filename) {
  FileHandler fh;
  auto lines = fh.readLines(filename);
  m_items.clear();

  for (const auto &line : lines) {
    std::stringstream ss(line);
    std::string customerId, playId;
    std::getline(ss, customerId, ',');
    std::getline(ss, playId, ',');
    add(customerId, playId);
  }
}

void TicketManager::saveToFile(const std::string &filename) const {
  FileHandler fh;
  std::vector<std::string> lines;

  for (const auto &ticket : m_items) {
    std::string line = ticket.getCustomerId() + "," + ticket.getPlayId();
    lines.push_back(line);
  }

  fh.writeLines(filename, lines);
}

Ticket *TicketManager::search(const std::string &id) const {
  auto it = m_ticketList.find(id);
  return (it != m_ticketList.end()) ? it->second : nullptr;
}

std::vector<Ticket> TicketManager::getAll() const {
  std::vector<Ticket> tickets;
  for (const auto &pair : m_ticketList) {
    tickets.push_back(*pair.second);
  }
  return tickets;
}

std::string TicketManager::makeId() const {
  static std::random_device rd;
  static std::mt19937 gen(rd());
  static std::uniform_int_distribution<> dis(10000, 99999);

  std::string id;
  do {
    id = "T" + std::to_string(dis(gen));
  } while (search(id) != nullptr);

  return id;
}
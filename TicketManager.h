// TicketManager.h
#pragma once

#include "Manager.h"
#include "Ticket.h"
#include <map>
#include <string>
#include <vector>

class TicketManager : public Manager<Ticket> {
public:
  TicketManager();
  virtual ~TicketManager();

  void add(const Ticket &ticket) override;
  void input() override;
  bool remove(const std::string &id) override;
  bool modify(const std::string &id) override;
  Ticket *search(const std::string &id) const override;
  std::vector<Ticket> getAll() const override;
  std::string makeId() const override;

  bool add(const std::string &customerId, const std::string &playId);
  bool remove(const std::string &customerId, const std::string &playId);
  std::vector<Ticket> getCustomerTickets(const std::string &customerId) const;
  std::vector<Ticket> getPlayTickets(const std::string &playId) const;

  void loadFromFile(const std::string &filename);
  void saveToFile(const std::string &filename) const;

private:
  std::map<std::string, Ticket *> m_ticketList;
  const std::string M_TICKET_FILE_NAME = "reservation.csv";
  std::string generateId() const;
};
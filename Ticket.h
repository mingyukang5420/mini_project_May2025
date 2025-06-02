// Ticket.h
#ifndef __TICKET_H__
#define __TICKET_H__

#include <ctime> // For time_t
#include <string>

class Ticket {
public:
  Ticket(int a_ticketId = 0, int a_customerId = 0, int a_playsId = 0,
         time_t a_reservedDate = 0, int a_quantity = 0);

  int getTicketId() const;
  int getCustomerId() const;
  int getPlaysId() const;
  time_t getReservedDate() const;
  int getQuantity() const;

  void setCustomerId(int a_customerId);
  void setPlaysId(int a_playsId);
  void setReservedDate(time_t a_reservedDate);
  void setQuantity(int a_quantity);

private:
  int m_ticketId;
  int m_customerId;
  int m_playsId;
  time_t m_reservedDate; // YYYY-MM-DD 형식으로 관리 (저장 시 변환)
  int m_quantity;
};

#endif // __TICKET_H__
// Ticket.cpp
#include "Ticket.h"

Ticket::Ticket(int a_ticketId, int a_customerId, int a_playsId,
               time_t a_reservedDate, int a_quantity)
    : m_ticketId(a_ticketId), m_customerId(a_customerId), m_playsId(a_playsId),
      m_reservedDate(a_reservedDate), m_quantity(a_quantity) {}

int Ticket::getTicketId() const { return m_ticketId; }

int Ticket::getCustomerId() const { return m_customerId; }

int Ticket::getPlaysId() const { return m_playsId; }

time_t Ticket::getReservedDate() const { return m_reservedDate; }

int Ticket::getQuantity() const { return m_quantity; }

void Ticket::setCustomerId(int a_customerId) { m_customerId = a_customerId; }

void Ticket::setPlaysId(int a_playsId) { m_playsId = a_playsId; }

void Ticket::setReservedDate(time_t a_reservedDate) {
  m_reservedDate = a_reservedDate;
}

void Ticket::setQuantity(int a_quantity) { m_quantity = a_quantity; }
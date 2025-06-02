// TicketManager.h
#ifndef __TICKET_MANAGER_H__
#define __TICKET_MANAGER_H__

#include "CustomerManager.h" // For customer validation
#include "PlayManager.h"     // For play validation
#include "Ticket.h"
#include <ctime> // For time_t
#include <map>
#include <memory> // For std::unique_ptr
#include <string>
#include <vector>

class TicketManager {
public:
  TicketManager(CustomerManager &a_customerManager, PlayManager &a_playManager);
  ~TicketManager();

  void addTicket(const Ticket &a_ticket);    // 티켓 추가 (ID 자동 생성)
  void inputTicket();                        // 사용자 입력으로 티켓 추가
  bool deleteTicket(int a_ticketId);         // 티켓 삭제
  bool modifyTicket(int a_ticketId);         // 티켓 정보 수정
  Ticket *searchTicket(int a_ticketId);      // 티켓 조회 (포인터 반환)
  std::vector<Ticket> getAllTickets() const; // 모든 티켓 정보 반환

private:
  std::map<int, std::unique_ptr<Ticket>> m_ticketList;
  const std::string M_RESERVATION_FILE_NAME = "reservation.csv";
  CustomerManager &m_customerManager; // 고객 유효성 검사를 위해 참조
  PlayManager &m_playManager;         // 연극 유효성 검사를 위해 참조

  void loadTicketsFromFile(); // 파일에서 티켓 정보 로드
  void saveTicketsToFile();   // 파일에 티켓 정보 저장
  int makeTicketId();         // 새로운 티켓 ID 생성

  // YYYY-MM-DD 문자열을 time_t로 변환
  time_t parseDate(const std::string &a_dateString);
  // time_t를 YYYY-MM-DD 문자열로 변환
  std::string formatDate(time_t a_time);
};

#endif // __TICKET_MANAGER_H__
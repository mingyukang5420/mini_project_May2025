// DisplayConsoleView.h
#ifndef __DISPLAY_CONSOLE_VIEW_H__
#define __DISPLAY_CONSOLE_VIEW_H__

#include <iomanip> // For std::setw, std::setfill, std::left, std::right
#include <iostream>
#include <string>
#include <vector>

// Forward declarations to avoid circular includes
class Customer;
class Play;
class Ticket;

class DisplayConsoleView {
public:
  // 메인 메뉴를 출력합니다.
  static void displayMainMenu();
  // 고객 관리 메뉴를 출력합니다.
  static void displayCustomerMenu();
  // 연극 관리 메뉴를 출력합니다.
  static void displayPlaysMenu();
  // 티켓 관리 메뉴를 출력합니다.
  static void displayTicketMenu();

  // 고객 목록을 출력합니다.
  static void displayCustomers(const std::vector<Customer> &a_customerList);
  // 특정 고객 정보를 출력합니다.
  static void displayCustomer(const Customer *a_customer);

  // 연극 목록을 출력합니다.
  static void displayPlays(const std::vector<Play> &a_playList);
  // 특정 연극 정보를 출력합니다.
  static void displayPlay(const Play *a_play);

  // 티켓 목록을 출력합니다.
  static void displayTickets(const std::vector<Ticket> &a_ticketList);
  // 특정 티켓 정보를 출력합니다.
  static void displayTicket(const Ticket *a_ticket);

  // 사용자에게 메시지를 출력합니다.
  static void showMessage(const std::string &a_message);
  // 사용자에게 에러 메시지를 출력합니다.
  static void showErrorMessage(const std::string &a_errorMessage);
  // 사용자 입력을 기다립니다.
  static void pressEnterToContinue();
  // 화면을 지웁니다.
  static void clearScreen();

private:
  DisplayConsoleView() = delete; // 정적 클래스로서 인스턴스화를 막음
  ~DisplayConsoleView() = delete;
};

#endif // __DISPLAY_CONSOLE_VIEW_H__
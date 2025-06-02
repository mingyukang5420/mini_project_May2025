// DisplayConsoleView.cpp
#include "DisplayConsoleView.h"
#include "Customer.h" // For Customer class definition
#include "Plays.h"    // For Plays class definition
#include "Ticket.h"   // For Ticket class definition
#include <iostream>

using namespace std;

void DisplayConsoleView::clearScreen() {
  // using ANSI escape codes to clear the screen.
  // In Windows, 'cls' command can be used, but for cross-platform
  // compatibility, ANSI code is used. If the terminal does not support ANSI
  // code, it may not work properly.
  std::cout << "\033[2J\033[1;1H";
}

void DisplayConsoleView::showMainMenu() {
  std::cout << "\n=== 공연 예매 시스템 ===\n"
            << "1. 고객 관리\n"
            << "2. 공연 관리\n"
            << "3. 예매 관리\n"
            << "4. 종료\n"
            << "선택: ";
}

void DisplayConsoleView::showCustomerMenu() {
  std::cout << "\n=== 고객 관리 ===\n"
            << "1. 고객 등록\n"
            << "2. 고객 조회\n"
            << "3. 고객 수정\n"
            << "4. 고객 삭제\n"
            << "5. 이전 메뉴\n"
            << "선택: ";
}

void DisplayConsoleView::showPlaysMenu() {
  std::cout << "\n=== 공연 관리 ===\n"
            << "1. 공연 등록\n"
            << "2. 공연 조회\n"
            << "3. 공연 수정\n"
            << "4. 공연 삭제\n"
            << "5. 이전 메뉴\n"
            << "선택: ";
}

void DisplayConsoleView::showTicketMenu() {
  std::cout << "\n=== 예매 관리 ===\n"
            << "1. 예매하기\n"
            << "2. 예매 조회\n"
            << "3. 예매 취소\n"
            << "4. 이전 메뉴\n"
            << "선택: ";
}

void DisplayConsoleView::showMessage(const std::string &message) {
  std::cout << "\n" << message << "\n";
}

void DisplayConsoleView::showErrorMessage(const std::string &message) {
  std::cerr << "\n오류: " << message << "\n";
}

std::string DisplayConsoleView::getInput(const std::string &prompt) {
  std::string input;
  std::cout << prompt;
  std::getline(std::cin, input);
  return input;
}

int DisplayConsoleView::getIntInput(const std::string &prompt) {
  while (true) {
    std::cout << prompt;
    std::string input;
    std::getline(std::cin, input);
    try {
      return std::stoi(input);
    } catch (...) {
      showErrorMessage("올바른 숫자를 입력해주세요.");
    }
  }
}

void DisplayConsoleView::displayCustomerList(
    const std::vector<std::string> &customers) {
  std::cout << "\n=== 고객 목록 ===\n";
  if (customers.empty()) {
    std::cout << "등록된 고객이 없습니다.\n";
    return;
  }
  for (const auto &customer : customers) {
    std::cout << customer << "\n";
  }
}

void DisplayConsoleView::displayPlaysList(
    const std::vector<std::string> &plays) {
  std::cout << "\n=== 공연 목록 ===\n";
  if (plays.empty()) {
    std::cout << "등록된 공연이 없습니다.\n";
    return;
  }
  for (const auto &play : plays) {
    std::cout << play << "\n";
  }
}

void DisplayConsoleView::displayTicketList(
    const std::vector<std::string> &tickets) {
  std::cout << "\n=== 예매 목록 ===\n";
  if (tickets.empty()) {
    std::cout << "예매 내역이 없습니다.\n";
    return;
  }
  for (const auto &ticket : tickets) {
    std::cout << ticket << "\n";
  }
}

void DisplayConsoleView::displayCustomer(const Customer *customer) {
  if (customer) {
    std::cout << "\n=== 고객 정보 ===\n"
              << "ID: " << customer->getId() << "\n"
              << "이름: " << customer->getName() << "\n"
              << "전화번호: " << customer->getPhone() << "\n";
  } else {
    showErrorMessage("고객 정보를 찾을 수 없습니다.");
  }
}

void DisplayConsoleView::displayPlay(const Plays *play) {
  if (play) {
    std::cout << "\n=== 공연 정보 ===\n"
              << "ID: " << play->getId() << "\n"
              << "제목: " << play->getTitle() << "\n"
              << "날짜: " << play->getDate() << "\n";
  } else {
    showErrorMessage("공연 정보를 찾을 수 없습니다.");
  }
}

void DisplayConsoleView::displayTicket(const Ticket *ticket) {
  if (ticket) {
    std::cout << "\n=== 예매 정보 ===\n"
              << "고객 ID: " << ticket->getCustomerId() << "\n"
              << "공연 ID: " << ticket->getPlayId() << "\n";
  } else {
    showErrorMessage("예매 정보를 찾을 수 없습니다.");
  }
}

void DisplayConsoleView::pressEnterToContinue() {
  std::cout << "\n계속하려면 Enter를 누르세요...";
  std::cin.get();
}
// DisplayConsoleView.cpp
#include "DisplayConsoleView.h"
#include "Customer.h" // For Customer class definition
#include "Play.h"     // For Play class definition
#include "Ticket.h"   // For Ticket class definition
#include <limits>     // For std::numeric_limits

using namespace std;

void DisplayConsoleView::clearScreen() {
  // ANSI 이스케이프 코드를 사용하여 화면을 지웁니다.
  // Windows 환경에서는 'cls' 명령어를 사용할 수 있지만, cross-platform을 위해
  // ANSI 코드를 사용합니다. 터미널이 ANSI 코드를 지원하지 않을 경우 제대로
  // 동작하지 않을 수 있습니다.
  cout << "\033[2J\033[1;1H";
}

void DisplayConsoleView::displayMainMenu() {
  clearScreen();
  cout << "+++++++++++++++++++++++++++++++++++++++++++++" << endl;
  cout << "              메인 메뉴                      " << endl;
  cout << "+++++++++++++++++++++++++++++++++++++++++++++" << endl;
  cout << "  1. 고객 관리                               " << endl;
  cout << "  2. 연극 관리                               " << endl;
  cout << "  3. 티켓 관리                               " << endl;
  cout << "  4. 프로그램 종료                           " << endl;
  cout << "+++++++++++++++++++++++++++++++++++++++++++++" << endl;
  cout << " 선택: ";
}

void DisplayConsoleView::displayCustomerMenu() {
  clearScreen();
  cout << "+++++++++++++++++++++++++++++++++++++++++++++" << endl;
  cout << "              고객 관리 메뉴                 " << endl;
  cout << "+++++++++++++++++++++++++++++++++++++++++++++" << endl;
  cout << "  1. 고객 목록 보기                          " << endl;
  cout << "  2. 고객 추가                               " << endl;
  cout << "  3. 고객 삭제                               " << endl;
  cout << "  4. 고객 정보 수정                          " << endl;
  cout << "  5. 메인 메뉴로 돌아가기                    " << endl;
  cout << "+++++++++++++++++++++++++++++++++++++++++++++" << endl;
  cout << " 선택: ";
}

void DisplayConsoleView::displayPlaysMenu() {
  clearScreen();
  cout << "+++++++++++++++++++++++++++++++++++++++++++++" << endl;
  cout << "              연극 관리 메뉴                 " << endl;
  cout << "+++++++++++++++++++++++++++++++++++++++++++++" << endl;
  cout << "  1. 연극 목록 보기                          " << endl;
  cout << "  2. 연극 추가                               " << endl;
  cout << "  3. 연극 삭제                               " << endl;
  cout << "  4. 연극 정보 수정                          " << endl;
  cout << "  5. 메인 메뉴로 돌아가기                    " << endl;
  cout << "+++++++++++++++++++++++++++++++++++++++++++++" << endl;
  cout << " 선택: ";
}

void DisplayConsoleView::displayTicketMenu() {
  clearScreen();
  cout << "+++++++++++++++++++++++++++++++++++++++++++++" << endl;
  cout << "              티켓 관리 메뉴                 " << endl;
  cout << "+++++++++++++++++++++++++++++++++++++++++++++" << endl;
  cout << "  1. 티켓 목록 보기                          " << endl;
  cout << "  2. 티켓 추가                               " << endl;
  cout << "  3. 티켓 삭제                               " << endl;
  cout << "  4. 티켓 정보 수정                          " << endl;
  cout << "  5. 메인 메뉴로 돌아가기                    " << endl;
  cout << "+++++++++++++++++++++++++++++++++++++++++++++" << endl;
  cout << " 선택: ";
}

void DisplayConsoleView::displayCustomers(
    const std::vector<Customer> &a_customerList) {
  clearScreen();
  cout << endl << "  ID  |     이름     |   전화번호   |         주소" << endl;
  cout << "--------------------------------------------------------" << endl;
  if (a_customerList.empty()) {
    cout << "등록된 고객이 없습니다." << endl;
  } else {
    for (const auto &customer : a_customerList) {
      cout << setw(5) << setfill('0') << right << customer.getCustomerId()
           << " | " << left;
      cout << setw(12) << setfill(' ') << customer.getCustomerName() << " | ";
      cout << setw(12) << customer.getPhoneNumber() << " | ";
      cout << customer.getAddress() << endl;
    }
  }
  cout << "--------------------------------------------------------" << endl;
  pressEnterToContinue();
}

void DisplayConsoleView::displayCustomer(const Customer *a_customer) {
  if (a_customer) {
    cout << endl
         << "  ID  |     이름     |   전화번호   |         주소" << endl;
    cout << "--------------------------------------------------------" << endl;
    cout << setw(5) << setfill('0') << right << a_customer->getCustomerId()
         << " | " << left;
    cout << setw(12) << setfill(' ') << a_customer->getCustomerName() << " | ";
    cout << setw(12) << a_customer->getPhoneNumber() << " | ";
    cout << a_customer->getAddress() << endl;
    cout << "--------------------------------------------------------" << endl;
  } else {
    showErrorMessage("고객 정보를 찾을 수 없습니다.");
  }
}

void DisplayConsoleView::displayPlays(const std::vector<Play> &a_playList) {
  clearScreen();
  cout << endl
       << "  ID  |      제목      |    장르    | 상영일(yyyy-mm-dd) |  가격  "
       << endl;
  cout << "---------------------------------------------------------------"
          "-------------------"
       << endl;
  if (a_playList.empty()) {
    cout << "등록된 연극이 없습니다." << endl;
  } else {
    for (const auto &play : a_playList) {
      cout << setw(5) << setfill('0') << right << play.getPlaysId() << " | "
           << left;
      cout << setw(14) << setfill(' ') << play.getPlaysName() << " | ";
      cout << setw(10) << play.getGenre() << " | ";

      // time_t를 YYYY-MM-DD 형식으로 변환하여 출력
      time_t showDate = play.getShowingDate();
      tm *ptm = localtime(&showDate);
      char buffer[11];
      strftime(buffer, sizeof(buffer), "%Y-%m-%d", ptm);
      cout << setw(18) << buffer << " | ";

      cout << setw(6) << fixed << setprecision(2) << play.getPrice() << endl;
      cout << "-------------------------------------------------------------"
              "---------------------"
           << endl;

      cout << setw(6) << fixed << setprecision(2) << play.getPrice() << endl;
    }
  }
  cout << "---------------------------------------------------------------"
          "-------------------"
       << endl;
  pressEnterToContinue();
}

void DisplayConsoleView::displayPlay(const Play *a_play) {
  if (a_play) {
    cout << endl
         << "  ID  |      제목      |    장르    | 상영일(yyyy-mm-dd) |  가격  "
         << endl;
    cout << "-------------------------------------------------------------"
            "---------------------"
         << endl;
    cout << setw(5) << setfill('0') << right << a_play->getPlaysId() << " | "
         << left;
    cout << setw(14) << setfill(' ') << a_play->getPlaysName() << " | ";
    cout << setw(10) << a_play->getGenre() << " | ";

    time_t showDate = a_play->getShowingDate();
    std::tm *ptm = std::localtime(&showDate);
    char buffer[11];
    strftime(buffer, sizeof(buffer), "%Y-%m-%d", ptm);
    cout << setw(18) << buffer << " | ";

    cout << setw(6) << fixed << setprecision(2) << a_play->getPrice() << endl;
    cout << "-------------------------------------------------------------"
            "---------------------"
         << endl;
  } else {
    showErrorMessage("연극 정보를 찾을 수 없습니다.");
  }
}

void DisplayConsoleView::displayTickets(
    const std::vector<Ticket> &a_ticketList) {
  clearScreen();
  cout << endl
       << "  ID  | 고객ID | 연극ID | 예매일(yyyy-mm-dd) | 수량 " << endl;
  cout << "------------------------------------------------------" << endl;
  if (a_ticketList.empty()) {
    cout << "등록된 티켓이 없습니다." << endl;
  } else {
    for (const auto &ticket : a_ticketList) {
      cout << setw(5) << setfill('0') << right << ticket.getTicketId() << " | ";
      cout << setw(6) << setfill('0') << right << ticket.getCustomerId()
           << " | ";
      cout << setw(6) << setfill('0') << right << ticket.getPlaysId() << " | ";

      // time_t를 YYYY-MM-DD 형식으로 변환하여 출력
      time_t reserveDate = ticket.getReservedDate();
      std::tm *ptm = std::localtime(&reserveDate);
      char buffer[11]; // YYYY-MM-DD\0
      strftime(buffer, sizeof(buffer), "%Y-%m-%d", ptm);
      cout << setw(18) << buffer << " | ";

      cout << setw(4) << setfill(' ') << right << ticket.getQuantity() << endl;
    }
  }
  cout << "------------------------------------------------------" << endl;
  pressEnterToContinue();
}

void DisplayConsoleView::displayTicket(const Ticket *a_ticket) {
  if (a_ticket) {
    cout << endl
         << "  ID  | 고객ID | 연극ID | 예매일(yyyy-mm-dd) | 수량 " << endl;
    cout << "------------------------------------------------------" << endl;
    cout << setw(5) << setfill('0') << right << a_ticket->getTicketId()
         << " | ";
    cout << setw(6) << setfill('0') << right << a_ticket->getCustomerId()
         << " | ";
    cout << setw(6) << setfill('0') << right << a_ticket->getPlaysId() << " | ";

    time_t reserveDate = a_ticket->getReservedDate();
    std::tm *ptm = std::localtime(&reserveDate);
    char buffer[11];
    strftime(buffer, sizeof(buffer), "%Y-%m-%d", ptm);
    cout << setw(18) << buffer << " | ";

    cout << setw(4) << setfill(' ') << right << a_ticket->getQuantity() << endl;
    cout << "------------------------------------------------------" << endl;
  } else {
    showErrorMessage("티켓 정보를 찾을 수 없습니다.");
  }
}

void DisplayConsoleView::showMessage(const std::string &a_message) {
  cout << endl << "[알림] " << a_message << endl;
}

void DisplayConsoleView::showErrorMessage(const std::string &a_errorMessage) {
  cout << endl << "[에러] " << a_errorMessage << endl;
}

void DisplayConsoleView::pressEnterToContinue() {
  cout << "\n계속하려면 Enter 키를 누르세요...";
  cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear buffer
  cin.get();                                           // Wait for Enter key
}
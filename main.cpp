// main.cpp
#include "CustomerManager.h"
#include "DisplayConsoleView.h"
#include "PlaysManager.h"
#include "TicketManager.h"
#include <iostream>
#include <limits>

using namespace std;

// Function for user input to select menu
int getMenuChoice() { // get the menu choice from the user
  int choice;         // the choice of the user
  while (!(cin >>
           choice)) { // if the input is not a number, show the error message
    DisplayConsoleView::showErrorMessage(
        "Invalid input. Please enter a number.");
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout << "Select: "; // show the select message
  }
  cin.ignore(numeric_limits<streamsize>::max(), '\n');
  return choice; // return the choice
}

class TheaterSystem {
private:
  CustomerManager customerManager;
  PlaysManager playsManager;
  TicketManager ticketManager;

public:
  void run() {
    while (true) {
      DisplayConsoleView::showMainMenu();
      int choice = DisplayConsoleView::getIntInput("");

      switch (choice) {
      case 1:
        handleCustomerMenu();
        break;
      case 2:
        handlePlaysMenu();
        break;
      case 3:
        handleTicketMenu();
        break;
      case 4:
        return;
      default:
        DisplayConsoleView::showErrorMessage("잘못된 선택입니다.");
      }
    }
  }

private:
  void handleCustomerMenu() {
    while (true) {
      DisplayConsoleView::showCustomerMenu();
      int choice = DisplayConsoleView::getIntInput("");

      switch (choice) {
      case 1: {
        std::string name = DisplayConsoleView::getInput("고객 이름: ");
        std::string phone = DisplayConsoleView::getInput("전화번호: ");
        customerManager.add(Customer(name, phone));
        DisplayConsoleView::showMessage("고객이 등록되었습니다.");
        break;
      }
      case 2: {
        auto customers = customerManager.getAll();
        std::vector<std::string> customerStrings;
        for (const auto &customer : customers) {
          customerStrings.push_back(customer.getId() + " - " +
                                    customer.getName() + " - " +
                                    customer.getPhone());
        }
        DisplayConsoleView::displayCustomerList(customerStrings);
        break;
      }
      case 3: {
        std::string id = DisplayConsoleView::getInput("수정할 고객 ID: ");
        Customer *customer = customerManager.search(id);
        if (customer) {
          std::string name = DisplayConsoleView::getInput("새 이름: ");
          std::string phone = DisplayConsoleView::getInput("새 전화번호: ");
          customer->setName(name);
          customer->setPhone(phone);
          DisplayConsoleView::showMessage("고객 정보가 수정되었습니다.");
        } else {
          DisplayConsoleView::showErrorMessage("고객을 찾을 수 없습니다.");
        }
        break;
      }
      case 4: {
        std::string id = DisplayConsoleView::getInput("삭제할 고객 ID: ");
        if (customerManager.remove(id)) {
          DisplayConsoleView::showMessage("고객이 삭제되었습니다.");
        } else {
          DisplayConsoleView::showErrorMessage("고객을 찾을 수 없습니다.");
        }
        break;
      }
      case 5:
        return;
      default:
        DisplayConsoleView::showErrorMessage("잘못된 선택입니다.");
      }
    }
  }

  void handlePlaysMenu() {
    while (true) {
      DisplayConsoleView::showPlaysMenu();
      int choice = DisplayConsoleView::getIntInput("");

      switch (choice) {
      case 1: {
        std::string title = DisplayConsoleView::getInput("공연 제목: ");
        std::string date = DisplayConsoleView::getInput("공연 날짜: ");
        playsManager.add(Plays(title, date));
        DisplayConsoleView::showMessage("공연이 등록되었습니다.");
        break;
      }
      case 2: {
        auto plays = playsManager.getAll();
        std::vector<std::string> playStrings;
        for (const auto &play : plays) {
          playStrings.push_back(play.getId() + " - " + play.getTitle() + " - " +
                                play.getDate());
        }
        DisplayConsoleView::displayPlaysList(playStrings);
        break;
      }
      case 3: {
        std::string id = DisplayConsoleView::getInput("수정할 공연 ID: ");
        Plays *play = playsManager.search(id);
        if (play) {
          std::string title = DisplayConsoleView::getInput("새 제목: ");
          std::string date = DisplayConsoleView::getInput("새 날짜: ");
          play->setTitle(title);
          play->setDate(date);
          DisplayConsoleView::showMessage("공연 정보가 수정되었습니다.");
        } else {
          DisplayConsoleView::showErrorMessage("공연을 찾을 수 없습니다.");
        }
        break;
      }
      case 4: {
        std::string id = DisplayConsoleView::getInput("삭제할 공연 ID: ");
        if (playsManager.remove(id)) {
          DisplayConsoleView::showMessage("공연이 삭제되었습니다.");
        } else {
          DisplayConsoleView::showErrorMessage("공연을 찾을 수 없습니다.");
        }
        break;
      }
      case 5:
        return;
      default:
        DisplayConsoleView::showErrorMessage("잘못된 선택입니다.");
      }
    }
  }

  void handleTicketMenu() {
    while (true) {
      DisplayConsoleView::showTicketMenu();
      int choice = DisplayConsoleView::getIntInput("");

      switch (choice) {
      case 1: {
        std::string customerId = DisplayConsoleView::getInput("고객 ID: ");
        std::string playId = DisplayConsoleView::getInput("공연 ID: ");
        if (customerManager.search(customerId) && playsManager.search(playId)) {
          if (ticketManager.add(customerId, playId)) {
            DisplayConsoleView::showMessage("예매가 완료되었습니다.");
          } else {
            DisplayConsoleView::showErrorMessage("예매에 실패했습니다.");
          }
        } else {
          DisplayConsoleView::showErrorMessage(
              "잘못된 고객 ID 또는 공연 ID입니다.");
        }
        break;
      }
      case 2: {
        std::string customerId = DisplayConsoleView::getInput("고객 ID: ");
        auto tickets = ticketManager.getCustomerTickets(customerId);
        std::vector<std::string> ticketStrings;
        for (const auto &ticket : tickets) {
          Plays *play = playsManager.search(ticket.getPlayId());
          if (play) {
            ticketStrings.push_back("고객 ID: " + ticket.getCustomerId() +
                                    " - 공연: " + play->getTitle() +
                                    " - 날짜: " + play->getDate());
          }
        }
        DisplayConsoleView::displayTicketList(ticketStrings);
        break;
      }
      case 3: {
        std::string customerId = DisplayConsoleView::getInput("고객 ID: ");
        std::string playId = DisplayConsoleView::getInput("공연 ID: ");
        if (ticketManager.remove(customerId, playId)) {
          DisplayConsoleView::showMessage("예매가 취소되었습니다.");
        } else {
          DisplayConsoleView::showErrorMessage("예매 정보를 찾을 수 없습니다.");
        }
        break;
      }
      case 4:
        return;
      default:
        DisplayConsoleView::showErrorMessage("잘못된 선택입니다.");
      }
    }
  }
};

int main() {
  TheaterSystem system;
  system.run();
  return 0;
}
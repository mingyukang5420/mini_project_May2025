// main.cpp
#include "CustomerManager.h"
#include "DisplayConsoleView.h"
#include "PlayManager.h"
#include "TicketManager.h"
#include <iostream>
#include <limits> // For std::numeric_limits

// using namespace std; // 전역으로 사용하도록 주석 해제

// 메뉴 선택을 위한 사용자 입력 함수
int getMenuChoice() {
  int choice;
  while (!(std::cin >> choice)) {
    DisplayConsoleView::showErrorMessage(
        "유효하지 않은 입력입니다. 숫자를 입력해주세요.");
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cout << "선택: ";
  }
  return choice;
}

int main() {
  CustomerManager customerManager;
  PlayManager playManager;
  TicketManager ticketManager(
      customerManager,
      playManager); // TicketManager는 CustomerManager와 PlayManager에 의존

  int mainChoice = 0;
  int subChoice = 0;
  int idToManage = 0;

  while (true) {
    DisplayConsoleView::displayMainMenu();
    mainChoice = getMenuChoice();

    switch (mainChoice) {
    case 1: // 고객 관리
      while (true) {
        DisplayConsoleView::displayCustomerMenu();
        subChoice = getMenuChoice();

        switch (subChoice) {
        case 1: // 고객 목록 보기
          DisplayConsoleView::displayCustomers(
              customerManager.getAllCustomers());
          break;
        case 2: // 고객 추가
          customerManager.inputCustomer();
          DisplayConsoleView::pressEnterToContinue();
          break;
        case 3: // 고객 삭제
          DisplayConsoleView::displayCustomers(
              customerManager.getAllCustomers());
          std::cout << "삭제할 고객 ID 입력: ";
          idToManage = getMenuChoice();
          customerManager.deleteCustomer(idToManage);
          DisplayConsoleView::pressEnterToContinue();
          break;
        case 4: // 고객 정보 수정
          DisplayConsoleView::displayCustomers(
              customerManager.getAllCustomers());
          std::cout << "수정할 고객 ID 입력: ";
          idToManage = getMenuChoice();
          customerManager.modifyCustomer(idToManage);
          DisplayConsoleView::pressEnterToContinue();
          break;
        case 5:                 // 메인 메뉴로 돌아가기
          goto endCustomerLoop; // 다중 루프 탈출
        default:
          DisplayConsoleView::showErrorMessage("잘못된 메뉴 선택입니다.");
          DisplayConsoleView::pressEnterToContinue();
          break;
        }
      }
    endCustomerLoop:;
      break;

    case 2: // 연극 관리
      while (true) {
        DisplayConsoleView::displayPlaysMenu();
        subChoice = getMenuChoice();

        switch (subChoice) {
        case 1: // 연극 목록 보기
          DisplayConsoleView::displayPlays(playManager.getAllPlays());
          break;
        case 2: // 연극 추가
          playManager.inputPlay();
          DisplayConsoleView::pressEnterToContinue();
          break;
        case 3: // 연극 삭제
          DisplayConsoleView::displayPlays(playManager.getAllPlays());
          std::cout << "삭제할 연극 ID 입력: ";
          idToManage = getMenuChoice();
          playManager.deletePlay(idToManage);
          DisplayConsoleView::pressEnterToContinue();
          break;
        case 4: // 연극 정보 수정
          DisplayConsoleView::displayPlays(playManager.getAllPlays());
          std::cout << "수정할 연극 ID 입력: ";
          idToManage = getMenuChoice();
          playManager.modifyPlay(idToManage);
          DisplayConsoleView::pressEnterToContinue();
          break;
        case 5: // 메인 메뉴로 돌아가기
          goto endPlayLoop;
        default:
          DisplayConsoleView::showErrorMessage("잘못된 메뉴 선택입니다.");
          DisplayConsoleView::pressEnterToContinue();
          break;
        }
      }
    endPlayLoop:;
      break;

    case 3: // 티켓 관리
      while (true) {
        DisplayConsoleView::displayTicketMenu();
        subChoice = getMenuChoice();

        switch (subChoice) {
        case 1: // 티켓 목록 보기
          DisplayConsoleView::displayTickets(ticketManager.getAllTickets());
          break;
        case 2: // 티켓 추가
          ticketManager.inputTicket();
          DisplayConsoleView::pressEnterToContinue();
          break;
        case 3: // 티켓 삭제
          DisplayConsoleView::displayTickets(ticketManager.getAllTickets());
          std::cout << "삭제할 티켓 ID 입력: ";
          idToManage = getMenuChoice();
          ticketManager.deleteTicket(idToManage);
          DisplayConsoleView::pressEnterToContinue();
          break;
        case 4: // 티켓 정보 수정
          DisplayConsoleView::displayTickets(ticketManager.getAllTickets());
          std::cout << "수정할 티켓 ID 입력: ";
          idToManage = getMenuChoice();
          ticketManager.modifyTicket(idToManage);
          DisplayConsoleView::pressEnterToContinue();
          break;
        case 5: // 메인 메뉴로 돌아가기
          goto endTicketLoop;
        default:
          DisplayConsoleView::showErrorMessage("잘못된 메뉴 선택입니다.");
          DisplayConsoleView::pressEnterToContinue();
          break;
        }
      }
    endTicketLoop:;
      break;

    case 4: // 프로그램 종료
      DisplayConsoleView::showMessage("프로그램을 종료합니다.");
      return 0;
    default:
      DisplayConsoleView::showErrorMessage("잘못된 메뉴 선택입니다.");
      DisplayConsoleView::pressEnterToContinue();
      break;
    }
  }

  return 0;
}
// TicketManager.cpp
#include "TicketManager.h"
#include "DisplayConsoleView.h"
#include "FileHandler.h"
#include <fstream>
#include <iomanip> // For std::put_time, std::get_time
#include <limits>
#include <sstream>

TicketManager::TicketManager(CustomerManager &a_customerManager,
                             PlayManager &a_playManager)
    : m_customerManager(a_customerManager), m_playManager(a_playManager) {
  loadTicketsFromFile();
}

TicketManager::~TicketManager() { saveTicketsToFile(); }

time_t TicketManager::parseDate(const std::string &a_dateString) {
  std::tm t = {};
  std::istringstream ss(a_dateString);
  ss >> std::get_time(&t, "%Y-%m-%d");
  if (ss.fail()) {
    DisplayConsoleView::showErrorMessage("날짜 파싱 실패: " + a_dateString);
    return 0; // 유효하지 않은 날짜일 경우 0 반환
  }
  return std::mktime(&t);
}

std::string TicketManager::formatDate(time_t a_time) {
  std::tm *ptm = std::localtime(&a_time);
  std::ostringstream ss;
  ss << std::put_time(ptm, "%Y-%m-%d");
  return ss.str();
}

void TicketManager::loadTicketsFromFile() {
  std::ifstream file(M_RESERVATION_FILE_NAME);
  if (!file.is_open()) {
    return;
  }

  while (!file.eof()) {
    std::vector<std::string> row = FileHandler::readCsvLine(file);
    if (row.empty())
      continue;

    if (row.size() < 5) {
      DisplayConsoleView::showErrorMessage(
          "reservation.csv 파일에서 유효하지 않은 데이터 형식을 발견했습니다. "
          "이 줄은 건너뜁니다.");
      continue;
    }

    try {
      int ticketId = std::stoi(row[0]);
      int customerId = std::stoi(row[1]);
      int playsId = std::stoi(row[2]);
      time_t reservedDate = parseDate(row[3]);
      int quantity = std::stoi(row[4]);

      // 유효성 검사: 고객 및 연극이 존재하는지 확인
      if (!m_customerManager.searchCustomer(customerId)) {
        DisplayConsoleView::showErrorMessage(
            "티켓 ID " + std::to_string(ticketId) + "의 고객 ID " +
            std::to_string(customerId) +
            "가 유효하지 않습니다. 이 티켓은 로드되지 않습니다.");
        continue;
      }
      if (!m_playManager.searchPlay(playsId)) {
        DisplayConsoleView::showErrorMessage(
            "티켓 ID " + std::to_string(ticketId) + "의 연극 ID " +
            std::to_string(playsId) +
            "가 유효하지 않습니다. 이 티켓은 로드되지 않습니다.");
        continue;
      }

      m_ticketList.insert(
          {ticketId, std::make_unique<Ticket>(ticketId, customerId, playsId,
                                              reservedDate, quantity)});
    } catch (const std::exception &e) {
      DisplayConsoleView::showErrorMessage(
          "reservation.csv 파일을 파싱하는 중 오류가 발생했습니다: " +
          std::string(e.what()));
    }
  }
  file.close();
}

void TicketManager::saveTicketsToFile() {
  std::ofstream file(M_RESERVATION_FILE_NAME);
  if (!file.is_open()) {
    DisplayConsoleView::showErrorMessage(
        "reservation.csv 파일을 저장할 수 없습니다.");
    return;
  }

  for (const auto &pair : m_ticketList) {
    const Ticket *ticket = pair.second.get();
    std::vector<std::string> data;
    data.push_back(std::to_string(ticket->getTicketId()));
    data.push_back(std::to_string(ticket->getCustomerId()));
    data.push_back(std::to_string(ticket->getPlaysId()));
    data.push_back(formatDate(
        ticket->getReservedDate())); // time_t를 문자열로 변환하여 저장
    data.push_back(std::to_string(ticket->getQuantity()));
    FileHandler::writeCsvLine(file, data);
  }
  file.close();
}

int TicketManager::makeTicketId() {
  if (m_ticketList.empty()) {
    return 1;
  } else {
    int maxId = 0;
    for (const auto &pair : m_ticketList) {
      if (pair.first > maxId) {
        maxId = pair.first;
      }
    }
    return maxId + 1;
  }
}

void TicketManager::addTicket(const Ticket &a_ticket) {
  m_ticketList.insert(
      {a_ticket.getTicketId(), std::make_unique<Ticket>(a_ticket)});
  saveTicketsToFile();
  DisplayConsoleView::showMessage("티켓 정보가 추가되었습니다.");
}

void TicketManager::inputTicket() {
  int customerId, playsId, quantity;
  std::string reservedDateStr;

  std::cout << "예매할 고객 ID : ";
  while (!(std::cin >> customerId) ||
         !m_customerManager.searchCustomer(customerId)) {
    DisplayConsoleView::showErrorMessage(
        "유효하지 않은 고객 ID입니다. 존재하는 고객 ID를 입력해주세요.");
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cout << "예매할 고객 ID : ";
  }
  std::cin.ignore(std::numeric_limits<std::streamsize>::max(),
                  '\n'); // 숫자 입력 후 남은 개행문자 처리

  std::cout << "예매할 연극 ID : ";
  while (!(std::cin >> playsId) || !m_playManager.searchPlay(playsId)) {
    DisplayConsoleView::showErrorMessage(
        "유효하지 않은 연극 ID입니다. 존재하는 연극 ID를 입력해주세요.");
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cout << "예매할 연극 ID : ";
  }
  std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

  std::cout << "예매 수량 : ";
  while (!(std::cin >> quantity) || quantity <= 0) {
    DisplayConsoleView::showErrorMessage(
        "유효하지 않은 수량입니다. 1 이상의 숫자를 입력해주세요.");
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cout << "예매 수량 : ";
  }
  std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

  // 현재 날짜를 예약일로 자동 설정 (MVP 범위)
  time_t reservedDate = std::time(nullptr);
  DisplayConsoleView::showMessage("예약일은 현재 날짜로 자동 설정됩니다: " +
                                  formatDate(reservedDate));

  int id = makeTicketId();
  m_ticketList.insert({id, std::make_unique<Ticket>(id, customerId, playsId,
                                                    reservedDate, quantity)});
  saveTicketsToFile();
  DisplayConsoleView::showMessage("새로운 티켓이 등록되었습니다. 티켓 ID: " +
                                  std::to_string(id));
}

bool TicketManager::deleteTicket(int a_ticketId) {
  auto it = m_ticketList.find(a_ticketId);
  if (it != m_ticketList.end()) {
    m_ticketList.erase(it);
    saveTicketsToFile();
    DisplayConsoleView::showMessage("티켓 ID " + std::to_string(a_ticketId) +
                                    "가 삭제되었습니다.");
    return true;
  } else {
    DisplayConsoleView::showErrorMessage(
        "티켓 ID " + std::to_string(a_ticketId) + "를 찾을 수 없습니다.");
    return false;
  }
}

bool TicketManager::modifyTicket(int a_ticketId) {
  Ticket *ticket = searchTicket(a_ticketId);
  if (ticket) {
    DisplayConsoleView::showMessage("현재 티켓 정보:");
    DisplayConsoleView::displayTicket(ticket);

    int newCustomerId = ticket->getCustomerId();
    int newPlaysId = ticket->getPlaysId();
    int newQuantity = ticket->getQuantity();
    bool changed = false;

    std::cout << "새로운 고객 ID (현재: " << newCustomerId << ") : ";
    std::string customerIdInput;
    std::getline(std::cin, customerIdInput); // 전체 라인을 읽고
    if (!customerIdInput.empty()) {
      std::stringstream ss(customerIdInput);
      int tempCustomerId;
      if (ss >> tempCustomerId &&
          m_customerManager.searchCustomer(tempCustomerId)) {
        newCustomerId = tempCustomerId;
        ticket->setCustomerId(newCustomerId);
        changed = true;
      } else {
        DisplayConsoleView::showErrorMessage(
            "유효하지 않거나 존재하지 않는 고객 ID입니다. 변경을 취소합니다.");
      }
    }

    std::cout << "새로운 연극 ID (현재: " << newPlaysId << ") : ";
    std::string playsIdInput;
    std::getline(std::cin, playsIdInput);
    if (!playsIdInput.empty()) {
      std::stringstream ss(playsIdInput);
      int tempPlaysId;
      if (ss >> tempPlaysId && m_playManager.searchPlay(tempPlaysId)) {
        newPlaysId = tempPlaysId;
        ticket->setPlaysId(newPlaysId);
        changed = true;
      } else {
        DisplayConsoleView::showErrorMessage(
            "유효하지 않거나 존재하지 않는 연극 ID입니다. 변경을 취소합니다.");
      }
    }

    std::cout << "새로운 수량 (현재: " << newQuantity << ") : ";
    std::string quantityInput;
    std::getline(std::cin, quantityInput);
    if (!quantityInput.empty()) {
      std::stringstream ss(quantityInput);
      int tempQuantity;
      if (ss >> tempQuantity && tempQuantity > 0) {
        newQuantity = tempQuantity;
        ticket->setQuantity(newQuantity);
        changed = true;
      } else {
        DisplayConsoleView::showErrorMessage(
            "유효하지 않은 수량입니다. 1 이상의 숫자를 입력해주세요. 변경을 "
            "취소합니다.");
      }
    }

    // 예약일은 변경하지 않는 것으로 가정합니다.

    if (changed) {
      saveTicketsToFile();
      DisplayConsoleView::showMessage("티켓 정보가 수정되었습니다.");
      return true;
    } else {
      DisplayConsoleView::showMessage("변경된 내용이 없습니다.");
      return false;
    }
  } else {
    DisplayConsoleView::showErrorMessage(
        "티켓 ID " + std::to_string(a_ticketId) + "를 찾을 수 없습니다.");
    return false;
  }
}

Ticket *TicketManager::searchTicket(int a_ticketId) {
  auto it = m_ticketList.find(a_ticketId);
  if (it != m_ticketList.end()) {
    return it->second.get();
  }
  return nullptr;
}

std::vector<Ticket> TicketManager::getAllTickets() const {
  std::vector<Ticket> tickets;
  for (const auto &pair : m_ticketList) {
    tickets.push_back(*(pair.second));
  }
  return tickets;
}
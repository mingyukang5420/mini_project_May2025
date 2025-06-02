// CustomerManager.cpp
#include "CustomerManager.h"
#include "DisplayConsoleView.h" // For displaying messages and input
#include "FileHandler.h"
#include <algorithm> // For std::max
#include <fstream>
#include <limits>  // For std::numeric_limits
#include <sstream> // For std::stringstream

CustomerManager::CustomerManager() { loadCustomersFromFile(); }

CustomerManager::~CustomerManager() {
  saveCustomersToFile();
  // unique_ptr을 사용했으므로 명시적인 delete는 필요 없습니다.
  // map이 소멸될 때 unique_ptr이 자동으로 메모리를 해제합니다.
}

void CustomerManager::loadCustomersFromFile() {
  std::ifstream file(M_CUSTOMER_FILE_NAME);
  if (!file.is_open()) {
    // 파일이 없거나 열 수 없으면 초기화할 필요 없음 (새로 시작)
    return;
  }

  while (!file.eof()) {
    std::vector<std::string> row = FileHandler::readCsvLine(file);
    if (row.empty())
      continue; // 빈 줄 건너뛰기

    // 데이터가 충분한지 확인
    if (row.size() < 4) {
      DisplayConsoleView::showErrorMessage(
          "customer.csv 파일에서 유효하지 않은 데이터 형식을 발견했습니다. 이 "
          "줄은 건너뜁니다.");
      continue;
    }

    try {
      int id = std::stoi(row[0]);
      std::string name = row[1];
      std::string phoneNumber = row[2];
      std::string address = row[3];
      m_customerList.insert(
          {id, std::make_unique<Customer>(id, name, phoneNumber, address)});
    } catch (const std::exception &e) {
      DisplayConsoleView::showErrorMessage(
          "customer.csv 파일을 파싱하는 중 오류가 발생했습니다: " +
          std::string(e.what()));
    }
  }
  file.close();
}

void CustomerManager::saveCustomersToFile() {
  std::ofstream file(M_CUSTOMER_FILE_NAME);
  if (!file.is_open()) {
    DisplayConsoleView::showErrorMessage(
        "customer.csv 파일을 저장할 수 없습니다.");
    return;
  }

  for (const auto &pair : m_customerList) {
    const Customer *customer = pair.second.get();
    std::vector<std::string> data;
    data.push_back(std::to_string(customer->getCustomerId()));
    data.push_back(customer->getCustomerName());
    data.push_back(customer->getPhoneNumber());
    data.push_back(customer->getAddress());
    FileHandler::writeCsvLine(file, data);
  }
  file.close();
}

int CustomerManager::makeCustomerId() {
  if (m_customerList.empty()) {
    return 1; // 첫 고객 ID는 1부터 시작
  } else {
    int maxId = 0;
    for (const auto &pair : m_customerList) {
      if (pair.first > maxId) {
        maxId = pair.first;
      }
    }
    return maxId + 1;
  }
}

void CustomerManager::addCustomer(const Customer &a_customer) {
  // 이 메서드는 외부에서 Customer 객체를 받아 직접 추가할 때 사용합니다.
  // makeCustomerId()로 생성한 ID를 부여하는 것이 아니라, 전달된 ID를
  // 사용합니다. 따라서 이 메서드는 내부적으로 사용되지 않거나, ID가 이미 부여된
  // Customer 객체를 추가할 때 유용합니다. 일반적으로 inputCustomer()를 통해
  // ID를 내부적으로 생성하여 추가하는 방식을 따릅니다. unique_ptr을 사용하므로,
  // 복사 생성자로 새로운 unique_ptr을 만들어 삽입합니다. 기존 객체를 복사하여
  // 새 객체를 생성하고 map에 추가합니다.
  m_customerList.insert(
      {a_customer.getCustomerId(), std::make_unique<Customer>(a_customer)});
  saveCustomersToFile();
  DisplayConsoleView::showMessage("고객 정보가 추가되었습니다.");
}

void CustomerManager::inputCustomer() {
  std::string name, phoneNumber, address;

  std::cout << "고객 이름 : ";
  std::cin.ignore(std::numeric_limits<std::streamsize>::max(),
                  '\n'); // 이전 입력 버퍼 비우기
  std::getline(std::cin, name);

  std::cout << "전화번호 : ";
  std::getline(std::cin, phoneNumber);

  std::cout << "주소 : ";
  std::getline(std::cin, address);

  int id = makeCustomerId();
  m_customerList.insert(
      {id, std::make_unique<Customer>(id, name, phoneNumber, address)});
  saveCustomersToFile();
  DisplayConsoleView::showMessage("새로운 고객이 등록되었습니다. ID: " +
                                  std::to_string(id));
}

bool CustomerManager::deleteCustomer(int a_customerId) {
  auto it = m_customerList.find(a_customerId);
  if (it != m_customerList.end()) {
    m_customerList.erase(it);
    saveCustomersToFile();
    DisplayConsoleView::showMessage("고객 ID " + std::to_string(a_customerId) +
                                    "가 삭제되었습니다.");
    return true;
  } else {
    DisplayConsoleView::showErrorMessage(
        "고객 ID " + std::to_string(a_customerId) + "를 찾을 수 없습니다.");
    return false;
  }
}

bool CustomerManager::modifyCustomer(int a_customerId) {
  Customer *customer = searchCustomer(a_customerId);
  if (customer) {
    DisplayConsoleView::showMessage("현재 고객 정보:");
    DisplayConsoleView::displayCustomer(customer);

    std::string newName, newPhoneNumber, newAddress;

    std::cout << "새로운 고객 이름 (현재: " << customer->getCustomerName()
              << ") : ";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::getline(std::cin, newName);
    if (!newName.empty()) { // 비어있지 않은 경우에만 수정
      customer->setCustomerName(newName);
    }

    std::cout << "새로운 전화번호 (현재: " << customer->getPhoneNumber()
              << ") : ";
    std::getline(std::cin, newPhoneNumber);
    if (!newPhoneNumber.empty()) {
      customer->setPhoneNumber(newPhoneNumber);
    }

    std::cout << "새로운 주소 (현재: " << customer->getAddress() << ") : ";
    std::getline(std::cin, newAddress);
    if (!newAddress.empty()) {
      customer->setAddress(newAddress);
    }

    saveCustomersToFile();
    DisplayConsoleView::showMessage("고객 정보가 수정되었습니다.");
    return true;
  } else {
    DisplayConsoleView::showErrorMessage(
        "고객 ID " + std::to_string(a_customerId) + "를 찾을 수 없습니다.");
    return false;
  }
}

Customer *CustomerManager::searchCustomer(int a_customerId) {
  auto it = m_customerList.find(a_customerId);
  if (it != m_customerList.end()) {
    return it->second.get(); // unique_ptr에서 원시 포인터 반환
  }
  return nullptr;
}

std::vector<Customer> CustomerManager::getAllCustomers() const {
  std::vector<Customer> customers;
  for (const auto &pair : m_customerList) {
    customers.push_back(
        *(pair.second)); // unique_ptr이 가리키는 Customer 객체 복사
  }
  return customers;
}
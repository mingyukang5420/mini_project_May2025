// CustomerManager.cpp
#include "CustomerManager.h"
#include "DisplayConsoleView.h" // For displaying messages and input
#include <fstream>
#include <random>
#include <sstream>

CustomerManager::CustomerManager() { loadFromFile("customer.csv"); }

CustomerManager::~CustomerManager() {
  saveToFile("customer.csv");
  for (auto &pair : m_customerList) {
    delete pair.second;
  }
}

void CustomerManager::add(const Customer &customer) {
  Customer newCustomer = customer;
  newCustomer.setId(generateId());
  Manager<Customer>::add(newCustomer);
}

void CustomerManager::input() {
  std::string name = DisplayConsoleView::getInput("고객 이름: ");
  std::string phone = DisplayConsoleView::getInput("전화번호: ");
  add(Customer(name, phone));
  DisplayConsoleView::showMessage("고객이 등록되었습니다.");
}

bool CustomerManager::remove(const std::string &id) {
  auto it = m_customerList.find(id);
  if (it != m_customerList.end()) {
    delete it->second;
    m_customerList.erase(it);
    saveToFile("customer.csv");
    DisplayConsoleView::showMessage("Customer ID " + id + " has been deleted.");
    return true;
  }
  DisplayConsoleView::showErrorMessage("Customer ID " + id + " not found.");
  return false;
}

bool CustomerManager::modify(const std::string &id) {
  Customer *customer = search(id);
  if (customer) {
    std::string name = DisplayConsoleView::getInput("새 이름: ");
    std::string phone = DisplayConsoleView::getInput("새 전화번호: ");
    if (!name.empty())
      customer->setName(name);
    if (!phone.empty())
      customer->setPhone(phone);
    DisplayConsoleView::showMessage("고객 정보가 수정되었습니다.");
    return true;
  }
  DisplayConsoleView::showErrorMessage("고객을 찾을 수 없습니다.");
  return false;
}

Customer *CustomerManager::search(const std::string &id) const {
  auto it = m_customerList.find(id);
  return (it != m_customerList.end()) ? it->second : nullptr;
}

std::vector<Customer> CustomerManager::getAll() const {
  std::vector<Customer> customers;
  for (const auto &pair : m_customerList) {
    customers.push_back(*pair.second);
  }
  return customers;
}

void CustomerManager::loadFromFile(const std::string &filename) {
  std::ifstream file(filename);
  if (!file.is_open())
    return;

  std::string line;
  while (std::getline(file, line)) {
    std::stringstream ss(line);
    std::string id, name, phone;
    std::getline(ss, id, ',');
    std::getline(ss, name, ',');
    std::getline(ss, phone, ',');

    if (!id.empty() && !name.empty()) {
      m_customerList[id] = new Customer(id, name, phone);
    }
  }
  file.close();
}

void CustomerManager::saveToFile(const std::string &filename) const {
  std::ofstream file(filename);
  if (!file.is_open()) {
    DisplayConsoleView::showErrorMessage("Cannot save to " + filename);
    return;
  }

  for (const auto &pair : m_customerList) {
    const Customer *customer = pair.second;
    file << customer->getId() << "," << customer->getName() << ","
         << customer->getPhone() << "\n";
  }
  file.close();
}

std::string CustomerManager::makeId() const { return generateId(); }

std::string CustomerManager::generateId() const {
  static std::random_device rd;
  static std::mt19937 gen(rd());
  static std::uniform_int_distribution<> dis(10000, 99999);

  std::string id;
  do {
    id = "C" + std::to_string(dis(gen));
  } while (search(id) != nullptr);

  return id;
}
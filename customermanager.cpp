#include "customermanager.h"
#include <algorithm>
#include <ctime>
#include <iomanip>
#include <iostream>
#include <sstream>

using namespace std;

CustomerManager::CustomerManager() { loadFromDatabase(); }

CustomerManager::~CustomerManager() {
  saveToDatabase();
  for (auto &pair : customerList) {
    delete pair.second;
  }
  customerList.clear();
}

bool CustomerManager::addCustomer(const Customer &customer) {
  try {
    if (checkDuplicateCustomer(customer.getCustomerName())) {
      cout << "이미 존재하는 고객입니다." << endl;
      return false;
    }

    int customerId = makeCustomerId();
    Customer *newCustomer = new Customer(customer); // 복사 생성자 사용
    newCustomer->setId(customerId);
    customerList[customerId] = newCustomer;

    return saveToDatabase();
  } catch (const exception &e) {
    cout << "고객 추가 중 오류 발생: " << e.what() << endl;
    return false;
  }
}

bool CustomerManager::removeCustomer(int customerId, const User *requester) {
  if (!hasPermission(requester, customerId)) {
    cout << "권한이 없습니다." << endl;
    return false;
  }

  auto it = customerList.find(customerId);
  if (it == customerList.end()) {
    cout << "고객을 찾을 수 없습니다." << endl;
    return false;
  }

  delete it->second;
  customerList.erase(it);
  return saveToDatabase();
}

bool CustomerManager::modifyCustomer(int customerId, const User *requester) {
  if (!hasPermission(requester, customerId)) {
    cout << "권한이 없습니다." << endl;
    return false;
  }

  auto it = customerList.find(customerId);
  if (it == customerList.end()) {
    cout << "고객을 찾을 수 없습니다." << endl;
    return false;
  }

  // TODO: 수정할 정보 입력 받기
  return saveToDatabase();
}

void CustomerManager::viewCustomer(int customerId, User *requester) const {
  if (!hasPermission(requester, customerId)) {
    cout << "권한이 없습니다." << endl;
    return;
  }

  Customer *customer = searchCustomer(customerId);
  if (customer) {
    cout << "\n=== 고객 정보 ===" << endl;
    cout << "ID: " << customer->getId() << endl;
    cout << "이름: " << customer->getCustomerName() << endl;
    cout << "주소: " << customer->getAddress() << endl;
    cout << "전화번호: " << customer->getPhoneNumber() << endl;
    cout << "가입일: " << customer->getRegisterDate() << endl;
    cout << "계좌 잔액: " << customer->getAccountBalance() << endl;
  } else {
    cout << "고객을 찾을 수 없습니다." << endl;
  }
}

Customer *CustomerManager::searchCustomer(int customerId) const {
  auto it = customerList.find(customerId);
  return (it != customerList.end()) ? it->second : nullptr;
}

vector<Customer *> CustomerManager::getAllCustomers() const {
  vector<Customer *> result;
  result.reserve(customerList.size());
  for (const auto &pair : customerList) {
    result.push_back(pair.second);
  }
  return result;
}

vector<Customer *> CustomerManager::filterCustomers(
    const function<bool(const Customer *)> &predicate) const {
  vector<Customer *> result;
  for (const auto &pair : customerList) {
    if (predicate(pair.second)) {
      result.push_back(pair.second);
    }
  }
  return result;
}

vector<Customer *>
CustomerManager::searchCustomersByName(const string &name) const {
  return filterCustomers([&name](const Customer *c) {
    return c->getCustomerName().find(name) != string::npos;
  });
}

vector<Customer *>
CustomerManager::searchCustomersByAddress(const string &address) const {
  return filterCustomers([&address](const Customer *c) {
    return c->getAddress().find(address) != string::npos;
  });
}

vector<Customer *>
CustomerManager::searchCustomersByRegisterDate(const string &date) const {
  return filterCustomers([&date](const Customer *c) {
    return c->getRegisterDate().find(date) != string::npos;
  });
}

bool CustomerManager::activateCustomer(int customerId) {
  auto it = customerList.find(customerId);
  if (it == customerList.end())
    return false;

  // TODO: 고객 상태 활성화 로직 구현
  return saveToDatabase();
}

bool CustomerManager::deactivateCustomer(int customerId) {
  auto it = customerList.find(customerId);
  if (it == customerList.end())
    return false;

  // TODO: 고객 상태 비활성화 로직 구현
  return saveToDatabase();
}

bool CustomerManager::updateCustomerBalance(int customerId, float amount) {
  auto it = customerList.find(customerId);
  if (it == customerList.end())
    return false;

  Customer *customer = it->second;
  float newBalance = customer->getAccountBalance() + amount;
  if (newBalance < 0) {
    cout << "잔액이 부족합니다." << endl;
    return false;
  }

  customer->deposit(amount); // deposit 메서드가 음수도 처리
  return saveToDatabase();
}

int CustomerManager::getTotalCustomerCount() const {
  return customerList.size();
}

int CustomerManager::getActiveCustomerCount() const {
  // TODO: 활성 상태 필드 추가 후 구현
  return customerList.size();
}

float CustomerManager::getTotalCustomerBalance() const {
  float total = 0.0f;
  for (const auto &pair : customerList) {
    total += pair.second->getAccountBalance();
  }
  return total;
}

vector<Customer *> CustomerManager::getTopCustomersByBalance(int limit) const {
  vector<Customer *> customers = getAllCustomers();
  sort(customers.begin(), customers.end(),
       [](const Customer *a, const Customer *b) {
         return a->getAccountBalance() > b->getAccountBalance();
       });

  if (static_cast<size_t>(limit) < customers.size()) {
    customers.resize(limit);
  }
  return customers;
}

vector<Customer *> CustomerManager::getRecentCustomers(int limit) const {
  vector<Customer *> customers = getAllCustomers();
  sort(customers.begin(), customers.end(),
       [](const Customer *a, const Customer *b) {
         return a->getRegisterDate() > b->getRegisterDate();
       });

  if (static_cast<size_t>(limit) < customers.size()) {
    customers.resize(limit);
  }
  return customers;
}

map<string, int> CustomerManager::getCustomersByRegion() const {
  map<string, int> regionCount;
  for (const auto &pair : customerList) {
    const string &address = pair.second->getAddress();
    // 주소에서 지역 추출 (첫 번째 공백까지를 지역으로 가정)
    string region = address.substr(0, address.find(' '));
    regionCount[region]++;
  }
  return regionCount;
}

bool CustomerManager::checkDuplicateCustomer(const string &name) const {
  return any_of(customerList.begin(), customerList.end(),
                [&name](const auto &pair) {
                  return pair.second->getCustomerName() == name;
                });
}

bool CustomerManager::isValidCustomerId(int customerId) const {
  return customerList.find(customerId) != customerList.end();
}

int CustomerManager::makeCustomerId() const {
  int maxId = 0;
  for (const auto &pair : customerList) {
    if (pair.first > maxId) {
      maxId = pair.first;
    }
  }
  return maxId + 1;
}

bool CustomerManager::saveToDatabase() const {
  try {
    vector<vector<string>> data;
    data.push_back({"CustomerID", "Name", "Address", "Phone", "CreditCard",
                    "Balance", "RegisterDate"});

    for (const auto &pair : customerList) {
      const Customer *customer = pair.second;
      vector<string> row;

      row.push_back(to_string(customer->getId()));
      row.push_back(customer->getCustomerName());
      row.push_back(customer->getAddress());
      row.push_back(customer->getPhoneNumber());
      row.push_back(customer->getCreditCardInfo());
      row.push_back(to_string(customer->getAccountBalance()));
      row.push_back(customer->getRegisterDate());

      data.push_back(row);
    }

    fileHandler.writeCsv("customers.csv", data);
    return true;
  } catch (const exception &e) {
    cout << "파일 저장 중 오류 발생: " << e.what() << endl;
    return false;
  }
}

bool CustomerManager::loadFromDatabase() {
  try {
    vector<vector<string>> data = fileHandler.readCsv("customers.csv");

    for (auto &pair : customerList) {
      delete pair.second;
    }
    customerList.clear();

    for (size_t i = 1; i < data.size(); i++) {
      const vector<string> &row = data[i];
      if (row.size() >= 7) {
        Customer *customer = new Customer();

        customer->setId(stoi(row[0]));
        customer->setCustomerName(row[1]);
        customer->setAddress(row[2]);
        customer->setPhoneNumber(row[3]);
        customer->setCreditCardInfo(row[4]);
        customer->deposit(stof(row[5])); // 잔액 설정
        // customer->setRegisterDate(row[6]);  // 이미 생성자에서 설정됨

        customerList[customer->getId()] = customer;
      }
    }

    return true;
  } catch (const exception &e) {
    cout << "파일 로드 중 오류 발생: " << e.what() << endl;
    return false;
  }
}

bool CustomerManager::hasPermission(const User *requester,
                                    int targetCustomerId) const {
  if (!requester)
    return false;

  if (requester->getUserType() == "admin") {
    return true; // 관리자는 모든 권한 있음
  }

  // 고객은 자신의 정보만 접근 가능
  if (requester->getUserType() == "customer") {
    const Customer *customerUser = dynamic_cast<const Customer *>(requester);
    return customerUser && customerUser->getId() == targetCustomerId;
  }

  return false;
}

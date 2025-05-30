#ifndef CUSTOMERMANAGER_H
#define CUSTOMERMANAGER_H

#include "customer.h"
#include "filehandler.h"
#include <functional>
#include <map>
#include <string>
#include <vector>

class CustomerManager {
public:
  CustomerManager();
  ~CustomerManager();

  // 기본 고객 관리
  bool addCustomer(const Customer &customer);
  bool removeCustomer(int customerId, const User *requester);
  bool modifyCustomer(int customerId, const User *requester);
  bool quitCustomer(int customerId, const User *requester);
  void viewCustomer(int customerId, User *requester) const;

  // 고객 조회 기능
  Customer *searchCustomer(int customerId) const;
  vector<Customer *> getAllCustomers() const;
  vector<Customer *> searchCustomersByName(const string &name) const;
  vector<Customer *> searchCustomersByAddress(const string &address) const;
  vector<Customer *> searchCustomersByRegisterDate(const string &date) const;

  // 고객 상태 관리
  bool activateCustomer(int customerId);
  bool deactivateCustomer(int customerId);
  bool updateCustomerBalance(int customerId, float amount);

  // 통계 및 분석
  int getTotalCustomerCount() const;
  int getActiveCustomerCount() const;
  float getTotalCustomerBalance() const;
  vector<Customer *> getTopCustomersByBalance(int limit) const;
  vector<Customer *> getRecentCustomers(int limit) const;
  map<string, int> getCustomersByRegion() const; // <region, count>

  // 유효성 검사
  bool checkDuplicateCustomer(const string &name) const;
  bool isValidCustomerId(int customerId) const;

private:
  map<int, Customer *> customerList;
  FileHandler fileHandler;

  // 유틸리티 함수
  int makeCustomerId() const;
  bool saveToDatabase();
  bool loadFromDatabase();

  // 내부 헬퍼 함수
  vector<Customer *>
  filterCustomers(const function<bool(const Customer *)> &predicate) const;
  bool hasPermission(const User *requester, int targetCustomerId) const;
};

#endif // CUSTOMERMANAGER_H

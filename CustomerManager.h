// CustomerManager.h
#ifndef __CUSTOMER_MANAGER_H__
#define __CUSTOMER_MANAGER_H__

#include "Customer.h"
#include <map>
#include <memory> // For std::unique_ptr
#include <string>
#include <vector>


class CustomerManager {
public:
  CustomerManager();
  ~CustomerManager();

  void addCustomer(const Customer &a_customer);  // 고객 추가 (ID 자동 생성)
  void inputCustomer();                          // 사용자 입력으로 고객 추가
  bool deleteCustomer(int a_customerId);         // 고객 삭제
  bool modifyCustomer(int a_customerId);         // 고객 정보 수정
  Customer *searchCustomer(int a_customerId);    // 고객 조회 (포인터 반환)
  std::vector<Customer> getAllCustomers() const; // 모든 고객 정보 반환

private:
  std::map<int, std::unique_ptr<Customer>>
      m_customerList; // unique_ptr을 사용하여 소유권 관리
  const std::string M_CUSTOMER_FILE_NAME = "customer.csv";

  void loadCustomersFromFile(); // 파일에서 고객 정보 로드
  void saveCustomersToFile();   // 파일에 고객 정보 저장
  int makeCustomerId();         // 새로운 고객 ID 생성
};

#endif // __CUSTOMER_MANAGER_H__
// CustomerManager.h
#pragma once

#include "Customer.h"
#include "Manager.h"
#include <map>
#include <string>
#include <vector>

class CustomerManager : public Manager<Customer> {
public:
  CustomerManager();
  virtual ~CustomerManager();

  void add(const Customer &customer) override; // 고객 추가 (ID 자동 생성)
  void input() override;                       // 사용자 입력으로 고객 추가
  bool remove(const std::string &id) override; // 고객 삭제
  bool modify(const std::string &id) override; // 고객 정보 수정
  Customer *search(const std::string &id) const override; // 고객 조회
  std::vector<Customer> getAll() const override;          // 모든 고객 정보 반환
  std::string makeId() const override;                    // ID 생성

  void loadFromFile(const std::string &filename);     // 파일에서 데이터 로드
  void saveToFile(const std::string &filename) const; // 파일에 데이터 저장

private:
  std::map<std::string, Customer *> m_customerList;
  const std::string M_CUSTOMER_FILE_NAME = "customer.csv";
  std::string generateId() const; // 내부 ID 생성 함수
};
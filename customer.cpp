#include "customer.h"
#include <algorithm>
#include <ctime>
#include <iomanip>
#include <sstream>


Customer::Customer()
    : customerId(0), customerName(""), address(""), phoneNumber(""),
      creditCardInfo(""), accountBalance(0.0f) {
  // 현재 날짜를 문자열로 변환하여 저장
  time_t now = time(0);
  tm *ltm = localtime(&now);
  stringstream ss;
  ss << put_time(ltm, "%Y-%m-%d");
  registerDate = ss.str();
}

Customer::~Customer() {
  // 민감한 정보 초기화
  customerName.clear();
  address.clear();
  phoneNumber.clear();
  creditCardInfo.clear();
  accountBalance = 0.0f;
  registerDate.clear();
}

void Customer::deposit(float amount) {
  if (amount > 0) {
    accountBalance += amount;
  }
}

bool Customer::withdraw(float amount) {
  if (amount > 0 && amount <= accountBalance) {
    accountBalance -= amount;
    return true;
  }
  return false;
}

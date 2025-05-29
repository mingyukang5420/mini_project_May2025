#include "accountregister.h"
#include "customermanager.h"
#include <iostream>
#include <string>
using namespace std;

AccountRegister::AccountRegister() {}
AccountRegister::~AccountRegister() {}

bool AccountRegister::isValidate(const string &newId) {
  // ID 형식 검사 (문자열만 허용)
  if (!isValidIdFormat(newId)) {
    cout << "Your entered ID is not valid." << endl;
    cout << "Please check the above message." << endl;
    return false;
  }

  // CustomerManager에 직접 중복 검사 요청
  CustomerManager customerManager;
  return !customerManager.checkDuplicateCustomer(newId);
}

bool AccountRegister::isValidIdFormat(const string &id) {
  // 빈 문자열 체크
  if (id.empty()) {
    cout << "Please enter your ID." << endl;
    return false;
  }

  // 모든 문자가 알파벳인지 확인 (단순 문자 비교 방식)
  for (char c : id) {
    if (!((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'))) {
      cout << "Please enter only alphabets for ID." << endl;
      return false;
    }
  }
  return true;
}

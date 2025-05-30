#include "user.h"
// #include "filehandler.h"
#include <algorithm>
#include <cctype> // isalpha, isdigit, ispunct 함수를 위해 추가
// #include <vector>

User::User() : userLoginId(""), password(""), userType("customer") {
  // 기본 생성자에서는 customer 타입으로 초기화
}

User::~User() {
  // 민감한 정보 초기화
  userLoginId.clear();
  password.clear();
  userType.clear();
}

bool User::verifyLogin(const string &id, const string &pw) {
  // 기본적인 로그인 검증
  return (id == userLoginId && pw == password);
}

// Setters 추가
void User::setUserLoginId(const string &id) {
  // 아이디 유효성 검사 (영문자와 숫자만 허용)
  bool isValid = true;
  for (size_t i = 0; i < id.length(); i++) {
    if (!std::isalnum(static_cast<unsigned char>(id[i]))) {
      isValid = false;
      break;
    }
  }
  if (isValid) {
    userLoginId = id;
  }
}

void User::setPassword(const string &pw) {
  // 비밀번호 유효성 검사 (최소 8자, 영문/숫자/특수문자 포함)
  if (pw.length() < 8)
    return;

  bool hasAlpha = false;
  bool hasDigit = false;
  bool hasPunct = false;

  for (size_t i = 0; i < pw.length(); i++) {
    unsigned char c = static_cast<unsigned char>(pw[i]);
    if (std::isalpha(c))
      hasAlpha = true;
    if (std::isdigit(c))
      hasDigit = true;
    if (std::ispunct(c))
      hasPunct = true;
  }

  if (hasAlpha && hasDigit && hasPunct) {
    password = pw;
  }
}

void User::setUserType(const string &type) {
  // 유효한 사용자 타입인지 확인
  if (type == "admin" || type == "customer") {
    userType = type;
  }
}

bool User::changePassword(const string &oldPw, const string &newPw) {
  // 기존 비밀번호 확인 후 변경
  if (password == oldPw) {
    setPassword(newPw);
    return true;
  }
  return false;
}

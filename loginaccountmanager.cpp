#include "loginaccountmanager.h"
#include <iostream>

LoginAccountManager::LoginAccountManager() { loadAccounts(); }

LoginAccountManager::~LoginAccountManager() {
  saveAccounts();
  // 동적 할당된 User 객체들 정리
  for (auto &pair : userAccounts) {
    delete pair.second;
  }
  userAccounts.clear();
}

bool LoginAccountManager::isValidIdFormat(const string &id) {
  // 빈 문자열 체크
  if (id.empty()) {
    cout << "ID를 입력해주세요." << endl;
    return false;
  }

  // 영문자만 허용 (AccountRegister에서 가져온 로직)
  for (char c : id) {
    if (!((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'))) {
      cout << "ID는 영문자만 사용 가능합니다." << endl;
      return false;
    }
  }
  return true;
}

bool LoginAccountManager::checkDuplicateId(const string &id) {
  return userAccounts.find(id) != userAccounts.end();
}

bool LoginAccountManager::createAccount(const string &id,
                                        const string &password,
                                        const string &userType) {
  // ID 유효성 검사
  if (!isValidIdFormat(id)) {
    return false;
  }

  // 중복 ID 검사
  if (checkDuplicateId(id)) {
    cout << "이미 존재하는 ID입니다." << endl;
    return false;
  }

  // 새 User 객체 생성
  User *newUser = new User();
  newUser->setUserLoginId(id);
  newUser->setPassword(password);
  newUser->setUserType(userType);

  // 계정 추가
  userAccounts[id] = newUser;
  return saveAccounts(); // 파일에 저장
}

bool LoginAccountManager::removeAccount(const string &id) {
  auto it = userAccounts.find(id);
  if (it != userAccounts.end()) {
    delete it->second;
    userAccounts.erase(it);
    return saveAccounts();
  }
  return false;
}

User *LoginAccountManager::verifyLogin(const string &id,
                                       const string &password) {
  // 계정 잠금 확인
  if (isAccountLocked(id)) {
    cout << "계정이 잠겼습니다. 관리자에게 문의하세요." << endl;
    return nullptr;
  }

  auto it = userAccounts.find(id);
  if (it != userAccounts.end() && it->second->verifyLogin(id, password)) {
    resetLoginAttempts(id); // 로그인 성공 시 시도 횟수 초기화
    return it->second;
  }

  // 로그인 실패 처리
  loginAttempts[id]++;
  cout << "로그인 실패: " << (MAX_LOGIN_ATTEMPTS - loginAttempts[id])
       << "회 남았습니다." << endl;
  return nullptr;
}

void LoginAccountManager::resetLoginAttempts(const string &id) {
  loginAttempts[id] = 0;
}

bool LoginAccountManager::isAccountLocked(const string &id) {
  return loginAttempts[id] >= MAX_LOGIN_ATTEMPTS;
}

bool LoginAccountManager::updatePassword(const string &id, const string &oldPw,
                                         const string &newPw) {
  auto it = userAccounts.find(id);
  if (it != userAccounts.end()) {
    if (it->second->changePassword(oldPw, newPw)) {
      return saveAccounts();
    }
  }
  return false;
}

bool LoginAccountManager::resetPassword(const string &id) {
  auto it = userAccounts.find(id);
  if (it != userAccounts.end()) {
    // 임시 비밀번호 생성 및 설정
    string tempPassword =
        "temp" + id + "123"; // 실제로는 더 복잡한 임시 비밀번호 생성 필요
    it->second->setPassword(tempPassword);
    return saveAccounts();
  }
  return false;
}

bool LoginAccountManager::saveAccounts() {
  try {
    vector<vector<string>> data;
    data.push_back({"LoginId", "Password", "UserType"}); // 헤더

    for (const auto &pair : userAccounts) {
      User *user = pair.second;
      data.push_back(
          {user->getUserLoginId(),
           "encrypted_" + user->getUserLoginId(), // 실제로는 암호화된 비밀번호
           user->getUserType()});
    }

    fileHandler.writeCsv("./sources/users.csv", data);
    return true; // 예외가 발생하지 않으면 성공으로 간주
  } catch (const exception &e) {
    cout << "계정 저장 중 오류 발생: " << e.what() << endl;
    return false;
  }
}

bool LoginAccountManager::loadAccounts() {
  try {
    vector<vector<string>> data = fileHandler.readCsv("./sources/users.csv");

    // 기존 데이터 정리
    for (auto &pair : userAccounts) {
      delete pair.second;
    }
    userAccounts.clear();

    // 첫 번째 줄은 헤더이므로 건너뜀
    for (size_t i = 1; i < data.size(); i++) {
      const auto &row = data[i];
      if (row.size() >= 3) {
        User *user = new User();
        user->setUserLoginId(row[0]);
        user->setPassword(row[1]); // 실제로는 암호화된 비밀번호 처리 필요
        user->setUserType(row[2]);
        userAccounts[row[0]] = user;
      }
    }
    return true;
  } catch (const exception &e) {
    cout << "계정 로드 중 오류 발생: " << e.what() << endl;
    return false;
  }
}
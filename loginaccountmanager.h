#ifndef LOGINACCOUNTMANAGER_H
#define LOGINACCOUNTMANAGER_H

#include "filehandler.h"
#include "user.h"
#include <map>
#include <string>

using namespace std;

class LoginAccountManager {
private:
  FileHandler fileHandler;
  map<string, User *> userAccounts; // loginId를 키로 사용
  static const int MAX_LOGIN_ATTEMPTS = 5;
  map<string, int> loginAttempts; // 사용자별 로그인 시도 횟수

  // AccountRegister에서 가져온 유효성 검사 메서드
  bool isValidIdFormat(const string &id);
  bool checkDuplicateId(const string &id);

public:
  LoginAccountManager();
  ~LoginAccountManager();

  // 계정 생성 및 관리
  bool createAccount(const string &id, const string &password,
                     const string &userType);
  bool removeAccount(const string &id);

  // 로그인 관련
  User *verifyLogin(const string &id, const string &password);
  void resetLoginAttempts(const string &id);
  bool isAccountLocked(const string &id);

  // 계정 정보 관리
  bool updatePassword(const string &id, const string &oldPw,
                      const string &newPw);
  bool resetPassword(const string &id);

  // 데이터 관리
  bool saveAccounts();
  bool loadAccounts();
};

#endif // LOGINACCOUNTMANAGER_H
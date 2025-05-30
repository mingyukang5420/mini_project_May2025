#ifndef LOGIN_CONTROLLER_H
#define LOGIN_CONTROLLER_H

#include "consoleview.h"
#include "customermanager.h"
#include "user.h"

class LoginController {
private:
  CustomerManager customerManager;
  ConsoleView consoleView;
  User *currentUser;
  bool isLoggedIn;

public:
  LoginController();
  ~LoginController();

  // 기본 로그인 기능
  bool login(const string &id, const string &password);
  void logout();
  bool signUp();

  // 상태 확인
  bool getLoginStatus() const { return isLoggedIn; }
  bool isAdmin() const {
    return currentUser && currentUser->getUserType() == "admin";
  }
  User *getCurrentUser() const { return currentUser; }
  Customer *getCurrentCustomer() const;
};

#endif
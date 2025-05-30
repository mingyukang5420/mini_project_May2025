#include "logincontroller.h"
#include "loginaccountmanager.h"
#include <iostream>

using namespace std;

LoginController::LoginController() : currentUser(nullptr), isLoggedIn(false) {}

LoginController::~LoginController() { logout(); }

bool LoginController::login(const string &id, const string &password) {
  LoginAccountManager accountManager;
  currentUser = accountManager.verifyLogin(id, password);

  if (currentUser) {
    isLoggedIn = true;
    cout << "로그인 성공!" << endl;
    if (isAdmin()) {
      cout << "관리자로 로그인했습니다." << endl;
    } else {
      cout << "사용자로 로그인했습니다." << endl;
    }
    return true;
  }

  cout << "로그인 실패: 아이디 또는 비밀번호가 잘못되었습니다." << endl;
  return false;
}

void LoginController::logout() {
  if (currentUser) {
    delete currentUser;
    currentUser = nullptr;
  }
  isLoggedIn = false;
}

bool LoginController::signUp() {
  LoginAccountManager accountManager;
  string id, password, userType;

  cout << "새 계정 등록\n";
  cout << "아이디: ";
  cin >> id;
  cout << "비밀번호: ";
  cin >> password;
  cout << "계정 유형 (admin/customer): ";
  cin >> userType;

  if (accountManager.createAccount(id, password, userType)) {
    cout << "계정이 성공적으로 생성되었습니다." << endl;
    return true;
  }

  cout << "계정 생성 실패" << endl;
  return false;
}

Customer *LoginController::getCurrentCustomer() const {
  if (!currentUser || currentUser->getUserType() != "customer") {
    return nullptr;
  }
  return dynamic_cast<Customer *>(currentUser);
}
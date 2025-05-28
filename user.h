#ifndef USER_H
#define USER_H

#include <iostream>

using namespace std;

class User {
public:
  User(string userLoginId, string = "", string = "", string = "", string = "",
       string = "");

  bool verifyLogin(string userLoginId, string password);

private:
  string m_userLoginId;
  string m_password;
  string m_loginStatus;
  string m_userType;
  string m_registerDate;
};

#endif // USER_H

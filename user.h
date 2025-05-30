#ifndef USER_H
#define USER_H

#include <string>
using namespace std;

class User {
private:
  string userLoginId; // login ID (example: "c001", "a01")
  string password;    // password
  string userType;    // "admin" or "customer"

public:
  User();
  virtual ~User();

  // Getters
  string getUserLoginId() const { return userLoginId; }
  string getUserType() const { return userType; }

  // Setters
  void setUserLoginId(const string &id);
  void setPassword(const string &pw);
  void setUserType(const string &type);

  // Login related
  bool verifyLogin(const string &id, const string &pw);
  bool changePassword(const string &oldPw, const string &newPw);
};

#endif

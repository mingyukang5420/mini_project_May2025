#ifndef USER_H
#define USER_H

#include <iostream>

using namespace std;

class User {
public:
  User(string userLoginId, string = "", string = "", string = "", string = "",
       string = "");

  string getName() const;
  void setName(string &);
  string getPhoneNumber() const;
  void setPhoneNumber(string &);
  string getAddress() const;
  void setAddress(string &);
  int id() const;
  bool operator==(const User &other) const;

private:
  int m_id;
  string m_name;
  string m_phoneNumber;
  string m_address;
};

#endif // USER_H

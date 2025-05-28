#ifndef CUSTOMER_H
#define CUSTOMER_H

#include "user.h"

class Customer : public User {
public:
  Customer();
  ~Customer();
  int getCustomerId();
  string getCustomerName();
  string getCustomerPhone(); // 하이픈 포함 문자열
  string getCustomerAddress();
  string getCustomerCreditCardInfo();
  float getCustomerAccountBalance();
  void deposit(float amount);
  void withdraw(float amount);

private:
  int m_id;
  string m_name;
  string m_phone;
  string m_address;
  string m_creditCardInfo;
  float m_accountBalance;
};
#endif // CUSTOMER_H

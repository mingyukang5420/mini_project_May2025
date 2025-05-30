#ifndef CUSTOMER_H
#define CUSTOMER_H

#include "user.h"
#include <string>
#include <vector>

class Customer : public User {
private:
  int customerId;
  string customerName;
  string address;
  string phoneNumber;
  string creditCardInfo;
  float accountBalance;
  string registerDate;

public:
  Customer();
  ~Customer() override;

  // Getters
  int getId() const { return customerId; }
  string getCustomerName() const { return customerName; }
  string getAddress() const { return address; }
  string getPhoneNumber() const { return phoneNumber; }
  string getCreditCardInfo() const { return creditCardInfo; }
  float getAccountBalance() const { return accountBalance; }
  string getRegisterDate() const { return registerDate; }

  // Setters
  void setId(int id) { customerId = id; }
  void setCustomerName(const string &name) { customerName = name; }
  void setAddress(const string &addr) { address = addr; }
  void setPhoneNumber(const string &phone) { phoneNumber = phone; }
  void setCreditCardInfo(const string &card) { creditCardInfo = card; }
  void setRegisterDate(const string &date) { registerDate = date; }

  // Account operations
  void deposit(float amount);
  bool withdraw(float amount);
};

#endif // CUSTOMER_H

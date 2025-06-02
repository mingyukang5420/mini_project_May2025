// Customer.h
#ifndef __CUSTOMER_H__
#define __CUSTOMER_H__

#include <string>

class Customer {
public:
  Customer(int a_id = 0, std::string a_name = "",
           std::string a_phoneNumber = "", std::string a_address = "");

  int getCustomerId() const;
  std::string getCustomerName() const;
  std::string getPhoneNumber() const;
  std::string getAddress() const;

  void setCustomerName(const std::string &a_name);
  void setPhoneNumber(const std::string &a_phoneNumber);
  void setAddress(const std::string &a_address);

private:
  int m_customerId;
  std::string m_customerName;
  std::string m_phoneNumber;
  std::string m_address;
};

#endif // __CUSTOMER_H__
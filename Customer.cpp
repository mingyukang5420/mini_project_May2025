// Customer.cpp
#include "Customer.h"

Customer::Customer(int a_id, std::string a_name, std::string a_phoneNumber,
                   std::string a_address)
    : m_customerId(a_id), m_customerName(a_name), m_phoneNumber(a_phoneNumber),
      m_address(a_address) {}

int Customer::getCustomerId() const { return m_customerId; }

std::string Customer::getCustomerName() const { return m_customerName; }

std::string Customer::getPhoneNumber() const { return m_phoneNumber; }

std::string Customer::getAddress() const { return m_address; }

void Customer::setCustomerName(const std::string &a_name) {
  m_customerName = a_name;
}

void Customer::setPhoneNumber(const std::string &a_phoneNumber) {
  m_phoneNumber = a_phoneNumber;
}

void Customer::setAddress(const std::string &a_address) {
  m_address = a_address;
}
// Customer.h
#pragma once
#include <string>

class Customer {
public:
  Customer(const std::string &name = "", const std::string &phone = "")
      : m_id(""), m_name(name), m_phone(phone) {}

  Customer(const std::string &id, const std::string &name,
           const std::string &phone)
      : m_id(id), m_name(name), m_phone(phone) {}

  const std::string &getId() const { return m_id; }
  const std::string &getName() const { return m_name; }
  const std::string &getPhone() const { return m_phone; }

  void setId(const std::string &id) { m_id = id; }
  void setName(const std::string &name) { m_name = name; }
  void setPhone(const std::string &phone) { m_phone = phone; }

private:
  std::string m_id;
  std::string m_name;
  std::string m_phone;
};
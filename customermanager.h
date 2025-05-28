#ifndef CUSTOMERMANAGER_H
#define CUSTOMERMANAGER_H
#include "customer.h"
#include <map>

class CustomerManager {
public:
  CustomerManager();
  ~CustomerManager();
  void addCustomer();
  bool checkDuplicateCustomer(const string &name);
  void removeCustomer(int, const User *);
  void modifyCustomer(int);
  void quitCustomer(int, const User *);
  void viewCustomer(int, User *);
  int makeCustomerId();
  Customer *searchCustomer(int);

private:
  map<int, Customer *> customerList;
};
#endif // CUSTOMERMANAGER_H

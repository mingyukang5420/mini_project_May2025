#ifndef CONSOLEVIEW_H
#define CONSOLEVIEW_H

#include "customer.h"
#include "loginaccountmanager.h"
#include "plays.h"
#include "reserved.h"
#include "shoppingcart.h"
#include "user.h"
#include <vector>

class ConsoleView {
private:
  LoginAccountManager *loginManager;

public:
  ConsoleView();
  ~ConsoleView();
  bool displayMainMenu();
  bool displayCartMenu();
  void displayCartInfo(ShoppingCart *);
  bool displayCustomerMenu();
  void displayCustomerInfo(Customer *);
  bool displayPlaysMenu();
  void displayPlaysInfo(const vector<Plays *> &playsList, int currentPage = 1);
  bool displayReservedMenu();
  void displayReservedInfo(Reserved *);
  bool displayAdminMenu();
  void displayAdminInfo();
  bool displayAccountRegisterMenu();
  bool displayLogin();
  bool displayUserDashboard();
};
#endif // CONSOLEVIEW_H

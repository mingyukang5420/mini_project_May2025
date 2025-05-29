#ifndef CONSOLEVIEW_H
#define CONSOLEVIEW_H

#include "customer.h"
#include "plays.h"
#include "reserved.h"
#include "shoppingcart.h"
#include "user.h"
#include <vector>

class ConsoleView {
public:
  ConsoleView();
  ~ConsoleView();
  bool displayAdminMenu();
  void displayAdminInfo();
  bool displayAccountRegisterMenu();
  bool displayCartMenu();
  void displayCartInfo(ShoppingCart *);
  bool displayCustomerMenu();
  void displayCustomerInfo(Customer *);
  bool displayMainMenu();
  bool displayPlaysMenu();
  void displayPlaysInfo(const vector<Plays *> &playsList, int currentPage = 1);
  bool displayReservedMenu();
  void displayReservedInfo(Reserved *);
  bool displayOuterUserMenu();
  bool displayInnerUserMenu();
};
#endif // CONSOLEVIEW_H

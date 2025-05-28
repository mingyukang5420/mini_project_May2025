#ifndef CONSOLEVIEW_H
#define CONSOLEVIEW_H

#include "user.h"

class ConsoleView {
public:
  ConsoleView();
  ~ConsoleView();
  bool displayAdminMenu();
  bool displayAdminInfo();
  bool displayAccountRegisterMenu();
  bool displayCartMenu();
  void displayCartInfo();
  bool displayCustomerMenu();
  void displayCustomerInfo();
  bool displayMainMenu();
  bool displayPlaysMenu();
  void displayPlaysInfo();
  bool displayReservedMenu();
  void displayReservedInfo();
  bool displayUserMenu();
};
#endif // CONSOLEVIEW_H

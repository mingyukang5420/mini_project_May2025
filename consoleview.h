#ifndef CONSOLEVIEW_H
#define CONSOLEVIEW_H

#include "user.h"

class ConsoleView {
public:
  ConsoleView();
  ~ConsoleView();
  void displayAdminInfo();
  bool displayAdminMenu();
  bool displayAccountRegisterMenu();
  void displayCartInfo();
  bool displayCartMenu();
  void displayCustomerInfo();
  bool displayCustomerMenu();
  bool displayMainMenu();
  void displayPlaysInfo();
  bool displayPlaysMenu();
  void displayReservedInfo();
  bool displayReservedMenu();
  bool displayUserMenu();
};
#endif // CONSOLEVIEW_H

// #include "accountregister.h"
// #include "administrator.h"
#include "consoleview.h"
// #include "customer.h"
// #include "customermanager.h"
// #include "filehandler.h"
// #include "logincontroller.h"
// #include "plays.h"
// #include "playsmanager.h"
// #include "reserved.h"
// #include "reservedmanager.h"
// #include "shoppingcart.h"
// #include "shoppingcartmanager.h"
// #include "user.h"

#include <iostream>

int main() {
  ConsoleView consoleView;

  // it's the main loop of the program
  while (consoleView.displayMainMenu()) {
    // execute the program while the function returns false
  }

  std::cout << "Program End" << std::endl;
  return 0;
}

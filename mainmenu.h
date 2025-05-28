#ifndef MAINMENU_H
#define MAINMENU_H

#include "consoleview.h"
#include "customermanager.h"
#include "user.h"

class MainMenu {
public:
  MainMenu();
  ~MainMenu();
  void signUp();
  void signIn();

private:
  CustomerManager *m_customerManager;
  User *m_loggedInUser;
  ConsoleView *m_consoleView;
};
#endif

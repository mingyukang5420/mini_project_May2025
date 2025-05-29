
#include "mainmenu.h"
#include "consoleview.h"

MainMenu::MainMenu() {}
MainMenu::~MainMenu() {}

void MainMenu::signUp() {
  ConsoleView *consoleView = new ConsoleView();
  consoleView->displayAccountRegisterMenu();
  delete consoleView;
}

void MainMenu::signIn() {
  ConsoleView *consoleView = new ConsoleView();
  consoleView->displayOuterUserMenu();
  delete consoleView;
}

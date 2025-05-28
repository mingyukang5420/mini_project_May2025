#include "consoleview.h"
#include "customermanager.h"
#include "filehandler.h"
#include "mainmenu.h"
#include "playsmanager.h"
#include "reservedmanager.h"
#include "shoppingcartmanager.h"
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

ConsoleView::ConsoleView() {}
ConsoleView::~ConsoleView() {}

// mainmenu could be changed to the login menu
bool ConsoleView::displayMainMenu() {
  int ch;
  MainMenu mainMenu;
  cout << "\033[2J\033[1;1H";
  cout << "+++++++++++++++++++++++++++++++++++++++++++++" << endl;
  cout << "|                Main Menu                  |" << endl;
  cout << "|                                           |" << endl;
  cout << "+++++++++++++++++++++++++++++++++++++++++++++" << endl;
  cout << "|1. SIGN IN                                 |" << endl;
  cout << "|2. SIGN UP                                 |" << endl;
  cout << "|                                           |" << endl;
  cout << "|                                           |" << endl;
  cout << "|9. Back to Default Menu                    |" << endl;
  cout << "|0. Quit this program                       |" << endl;
  cout << "+++++++++++++++++++++++++++++++++++++++++++++" << endl;
  cin >> ch;
  switch (ch) {
  case 1:
    mainMenu.signIn();
    break;
  case 2:
    mainMenu.signUp();
    break;
  case 9:
    this->displayMainMenu();
    break;
  case 0:
    return false;
  }
  return true;
}
// nullptr is for the future implementation
bool ConsoleView::displayCartMenu() {
  int ch;
  int customerId;
  ShoppingCartManager shoppingCartManager;
  cout << "\033[2J\033[1;1H";
  cout << "+++++++++++++++++++++++++++++++++++++++++++++" << endl;
  cout << "|                Cart Menu                  |" << endl;
  cout << "|                                           |" << endl;
  cout << "+++++++++++++++++++++++++++++++++++++++++++++" << endl;
  cout << "|1. Add Cart                                |" << endl;
  cout << "|2. Cancel Cart                             |" << endl;
  cout << "|3. Remove Cart                             |" << endl;
  cout << "|4. Modify Cart                             |" << endl;
  cout << "|5. View Cart                               |" << endl;
  cout << "|6. Search Cart                             |" << endl;
  cout << "|7. Pay Cart                                |" << endl;
  cout << "|                                           |" << endl;
  cout << "|9. Back to Default Menu                    |" << endl;
  cout << "|0. Quit this program                       |" << endl;
  cout << "+++++++++++++++++++++++++++++++++++++++++++++" << endl;
  cin >> ch;
  switch (ch) {
  case 1:
    shoppingCartManager.addCart();
    break;
  case 2:
    shoppingCartManager.cancelCart(customerId);
    break;
  case 3:
    shoppingCartManager.removeCart(customerId);
    break;
  case 4:
    shoppingCartManager.modifyCart(customerId);
    break;
  case 5:
    // 임시로 null을 전달하고, 나중에 실제 장바구니를 구현해야 함
    shoppingCartManager.viewCart(nullptr);
    break;
  case 6:
    shoppingCartManager.searchCart(customerId);
    break;
  case 7:
    shoppingCartManager.pay(nullptr);
    break;
  case 9:
    this->displayMainMenu();
    break;
  case 0:
    return false;
  }
  return true;
}

// nullptr is for the future implementation
bool ConsoleView::displayCustomerMenu() {
  CustomerManager customerManager;
  int ch;
  int customerId;
  cout << "\033[2J\033[1;1H";
  cout << "+++++++++++++++++++++++++++++++++++++++++++++" << endl;
  cout << "|                Customer Menu              |" << endl;
  cout << "|                                           |" << endl;
  cout << "+++++++++++++++++++++++++++++++++++++++++++++" << endl;
  cout << "|1. Add Customer                            |" << endl;
  cout << "|2. Remove Customer                         |" << endl;
  cout << "|3. Modify Customer                         |" << endl;
  cout << "|4. Quit Customer Account                   |" << endl;
  cout << "|5. View Customer List                      |" << endl;
  cout << "|6. Search Customer Info                    |" << endl;
  cout << "|                                           |" << endl;
  cout << "|                                           |" << endl;
  cout << "|9. Back to Default Menu                    |" << endl;
  cout << "|0. Quit this program                       |" << endl;
  cout << "+++++++++++++++++++++++++++++++++++++++++++++" << endl;
  cin >> ch;
  switch (ch) {
  case 1:
    customerManager.addCustomer();
    break;
  case 2:
    customerManager.removeCustomer(customerId, nullptr);
    break;
  case 3:
    customerManager.modifyCustomer(customerId, nullptr);
    break;
  case 4:
    customerManager.quitCustomer(customerId, nullptr);
    break;
  case 5:
    customerManager.viewCustomer(customerId, nullptr);
    break;
  case 6:
    customerManager.searchCustomer(customerId);
    break;
  case 9:
    this->displayMainMenu();
    break;
  case 0:
    return false;
  }
  return true;
}

// nullptr is for the future implementation
bool ConsoleView::displayPlaysMenu() {
  int ch;
  int playsId;
  PlaysManager playsManager;
  cout << "\033[2J\033[1;1H";
  cout << "+++++++++++++++++++++++++++++++++++++++++++++" << endl;
  cout << "|                Plays Menu                 |" << endl;
  cout << "|                                           |" << endl;
  cout << "+++++++++++++++++++++++++++++++++++++++++++++" << endl;
  cout << "|1. Add Plays                               |" << endl;
  cout << "|2. Remove Plays                            |" << endl;
  cout << "|3. Modify Plays                            |" << endl;
  cout << "|4. Search Plays Info                       |" << endl;
  cout << "|5. View Plays List                         |" << endl;
  cout << "|                                           |" << endl;
  cout << "|                                           |" << endl;
  cout << "|9. Back to Default Menu                    |" << endl;
  cout << "|0. Quit this program                       |" << endl;
  cout << "+++++++++++++++++++++++++++++++++++++++++++++" << endl;
  cin >> ch;
  switch (ch) {
  case 1:
    playsManager.addPlays();
    break;
  case 2:
    playsManager.removePlays(playsId, nullptr);
    break;
  case 3:
    playsManager.modifyPlays(playsId, nullptr);
    break;
  case 4:
    playsManager.searchPlays(playsId);
    break;
  case 5:
    playsManager.viewPlays();
    break;
  case 9:
    this->displayMainMenu();
    break;
  case 0:
    return false;
  }
  return true;
}

// nullptr is for the future implementation
bool ConsoleView::displayReservedMenu() {
  int ch;
  int reservedId;
  ReservedManager reservedManager;
  cout << "\033[2J\033[1;1H";
  cout << "+++++++++++++++++++++++++++++++++++++++++++++" << endl;
  cout << "|                Reserved Menu              |" << endl;
  cout << "|                                           |" << endl;
  cout << "+++++++++++++++++++++++++++++++++++++++++++++" << endl;
  cout << "|1. Add Reserved                            |" << endl;
  cout << "|2. Remove Reserved                         |" << endl;
  cout << "|3. Modify Reserved                         |" << endl;
  cout << "|4. Search Reserved Info                    |" << endl;
  cout << "|5. View Reserved List                      |" << endl;
  cout << "|                                           |" << endl;
  cout << "|                                           |" << endl;
  cout << "|9. Back to Default Menu                    |" << endl;
  cout << "|0. Quit this program                       |" << endl;
  cout << "+++++++++++++++++++++++++++++++++++++++++++++" << endl;
  cin >> ch;
  switch (ch) {
  case 1:
    reservedManager.addReserved();
    break;
  case 2:
    reservedManager.removeReserved(reservedId, nullptr);
    break;
  case 3:
    reservedManager.modifyReserved(reservedId, nullptr);
    break;
  case 4:
    reservedManager.searchReserved(reservedId);
    break;
  case 5:
    reservedManager.viewReserved();
    break;
  case 9:
    this->displayMainMenu();
    break;
  case 0:
    return false;
  }
  return true;
}

bool ConsoleView::displayAdminMenu() {
  int ch;
  cout << "\033[2J\033[1;1H";
  cout << "+++++++++++++++++++++++++++++++++++++++++++++" << endl;
  cout << "|                Admin Menu                 |" << endl;
  cout << "|      Let me know what do you wanna do     |" << endl;
  cout << "|                                           |" << endl;
  cout << "|     CAUTION: You CAN'T GET BACK here      |" << endl;
  cout << "|              IF YOU LEAVE this menu       |" << endl;
  cout << "|                                           |" << endl;
  cout << "+++++++++++++++++++++++++++++++++++++++++++++" << endl;
  cout << "|1. View Admin Info                         |" << endl;
  cout << "|2. Goto Cart Menu                          |" << endl;
  cout << "|3. Goto Customer Menu                      |" << endl;
  cout << "|4. Goto Play Menu                          |" << endl;
  cout << "|5. Goto Reserved Menu                      |" << endl;
  cout << "|                                           |" << endl;
  cout << "|                                           |" << endl;
  cout << "|0. Quit this program                       |" << endl;
  cout << "+++++++++++++++++++++++++++++++++++++++++++++" << endl;
  cin >> ch;
  switch (ch) {
  case 1:
  default:
    this->displayAdminInfo();
    cin.ignore();
    getchar();
    break;
  case 2:
    displayCartMenu();
    cin.ignore();
    getchar();
    break;
  case 3:
    displayCustomerMenu();
    cin.ignore();
    getchar();
    break;
  case 4:
    displayPlaysMenu();
    cin.ignore();
    getchar();
    break;
  case 5:
    displayReservedMenu();
    cin.ignore();
    getchar();
    break;
  case 0:
    return false;
  }
  return true;
}

bool ConsoleView::displayAccountRegisterMenu() {
  int ch;
  CustomerManager customerManager;
  cout << "\033[2J\033[1;1H";
  cout << "+++++++++++++++++++++++++++++++++++++++++++++" << endl;
  cout << "|           Account Register Menu           |" << endl;
  cout << "|                                           |" << endl;
  cout << "+++++++++++++++++++++++++++++++++++++++++++++" << endl;
  cout << "|                                           |" << endl;
  cout << "| - Type your personal information          |" << endl;
  cout << "|   to register new account                 |" << endl;
  cout << "|   when the text printed                   |" << endl;
  cout << "|                                           |" << endl;
  cout << "| - Or type the number 9 and 0              |" << endl;
  cout << "|   to move to the other menu               |" << endl;
  cout << "|   or exit this program                    |" << endl;
  cout << "|                                           |" << endl;
  cout << "|                                           |" << endl;
  cout << "|9. Back to Default Menu                    |" << endl;
  cout << "|0. Quit this program                       |" << endl;
  cout << "+++++++++++++++++++++++++++++++++++++++++++++" << endl;
  cin >> ch;
  switch (ch) {
  default:
    this->displayAccountRegisterMenu();
    cin.ignore();
    getchar();
    customerManager.addCustomer();
    break;
  case 9:
    this->displayMainMenu();
    break;
  case 0:
    return false;
  }
  return true;
}

bool ConsoleView::displayUserMenu() {
  int ch;
  cout << "\033[2J\033[1;1H";
  cout << "+++++++++++++++++++++++++++++++++++++++++++++" << endl;
  cout << "|                User Menu                  |" << endl;
  cout << "|                                           |" << endl;
  cout << "+++++++++++++++++++++++++++++++++++++++++++++" << endl;
  cout << "|1. View User Info                          |" << endl;
  cout << "|2. Goto Cart Menu                          |" << endl;
  cout << "|3. Goto Customer Menu                      |" << endl;
  cout << "|4. Goto Play Menu                          |" << endl;
  cout << "|5. Goto Reserved Menu                      |" << endl;
  cout << "|                                           |" << endl;
  cout << "|                                           |" << endl;
  cout << "|9. Back to Default Menu                    |" << endl;
  cout << "|0. Quit this program                       |" << endl;
  cout << "+++++++++++++++++++++++++++++++++++++++++++++" << endl;
  cin >> ch;
  switch (ch) {
  case 1:
    this->displayUserInfo();
    break;
  case 2:
    this->displayCartMenu();
    break;
  }
  bool ConsoleView::displayAdminInfo() {
    const int ID_WIDTH = 10;
    const int NAME_WIDTH = 15;
    const int PW_WIDTH = 15;
    const int TOTAL_WIDTH = ID_WIDTH + NAME_WIDTH + PW_WIDTH +
                            10; // 10은 구분자와 여백을 위한 추가 공간

    cout << "\033[2J\033[1;1H";
    cout << string(TOTAL_WIDTH, '+') << endl;

    cout << "|" << setw((TOTAL_WIDTH - 2) / 2) << "Admin Info"
         << setw((TOTAL_WIDTH - 2) / 2) << "|" << endl;

    cout << "|" << setw(TOTAL_WIDTH - 2) << "These are the admin's information"
         << "|" << endl;

    cout << "|" << setw(TOTAL_WIDTH - 2) << " " << "|" << endl;

    cout << "|" << setw(TOTAL_WIDTH - 2) << "CAUTION: It's SECRET information"
         << "|" << endl;

    cout << "|" << setw(TOTAL_WIDTH - 2) << "be careful not to show" << "|"
         << endl;

    cout << "|" << setw(TOTAL_WIDTH - 2) << " " << "|" << endl;

    cout << string(TOTAL_WIDTH, '+') << endl;

    FileHandler fileHandler;
    vector<vector<string>> admin = fileHandler.readCsv("./sources/admin.csv");

    // 헤더 출력
    cout << "|" << setfill(' ') << setw((ID_WIDTH - 2) / 2) << " " << "ID"
         << setw((ID_WIDTH - 2) / 2) << " " << "|" << setw(NAME_WIDTH) << left
         << "Name" << "|" << setw(PW_WIDTH) << right << "Password" << "|"
         << endl;
    cout << string(TOTAL_WIDTH, '+') << endl;

    // 데이터 출력
    for (const auto &row : admin) {
      // ID 가운데 정렬
      string id = row[0];
      int padding = (ID_WIDTH - id.length()) / 2;
      cout << "|" << setfill(' ') << setw(padding) << " " << id
           << setw(ID_WIDTH - padding - id.length()) << " " << "|"
           << setw(NAME_WIDTH) << left << row[1] << "|" // Name 왼쪽 정렬
           << setw(PW_WIDTH) << right << row[2] << "|"
           << endl; // Password 오른쪽 정렬
    }
    cout << string(TOTAL_WIDTH, '+') << endl;
    return true;
  }

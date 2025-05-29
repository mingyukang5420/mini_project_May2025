#include "consoleview.h"
#include "customermanager.h"
#include "filehandler.h"
#include "mainmenu.h"
#include "playsmanager.h"
#include "reservedmanager.h"
#include "shoppingcartmanager.h"
#include <chrono>
#include <iomanip>
#include <iostream>
#include <string>
#include <thread>
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
  cout << "|5. View My Cart                            |" << endl;
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
  cout << "|9. Back to previous Menu                   |" << endl;
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

bool ConsoleView::displayInnerUserMenu() {
  int ch;
  cout << "\033[2J\033[1;1H";
  cout << "+++++++++++++++++++++++++++++++++++++++++++++" << endl;
  cout << "|                User Menu                  |" << endl;
  cout << "|                                           |" << endl;
  cout << "+++++++++++++++++++++++++++++++++++++++++++++" << endl;
  cout << "|1. Goto Cart Menu                          |" << endl;
  cout << "|2. Goto Personal Menu                      |" << endl;
  cout << "|3. Goto Plays Menu                         |" << endl;
  cout << "|4. Goto Reserved Menu                      |" << endl;
  cout << "|5. Logout                                  |" << endl;
  cout << "|                                           |" << endl;
  cout << "|                                           |" << endl;
  cout << "|0. Quit this program                       |" << endl;
  cout << "+++++++++++++++++++++++++++++++++++++++++++++" << endl;
  cin >> ch;
  switch (ch) {
  default:
    this->displayInnerUserMenu();
    cin.ignore();
    getchar();
    break;
  case 1:
    displayCartMenu();
    cin.ignore();
    getchar();
    break;
  case 2:
    displayCustomerMenu();
    break;
  case 3:
    displayPlaysMenu();
    break;
  case 4:
    displayReservedMenu();
    break;
  case 5:
    displayMainMenu();
    break;
  case 0:
    return false;
  }
  return true;
}

bool ConsoleView::displayOuterUserMenu() {
  User user;
  string id;
  string password;
  string userResponse;
  cout << "\033[2J\033[1;1H";
  cout << "+++++++++++++++++++++++++++++++++++++++++++++" << endl;
  cout << "|                User Menu                  |" << endl;
  cout << "|                                           |" << endl;
  cout << "+++++++++++++++++++++++++++++++++++++++++++++" << endl;
  cout << "|                                           |" << endl;
  cout << "| - Enter your Id and Password to sign in   |" << endl;
  cout << "|                                           |" << endl;
  cout << "|                                           |" << endl;
  cout << "|9. Back to Default Menu                    |" << endl;
  cout << "|0. Quit this program                       |" << endl;
  cout << "+++++++++++++++++++++++++++++++++++++++++++++" << endl;
  cout << "| ID :                                      |" << endl;
  cin >> id;
  cout << "| Entered Your ID : " << id << setw(22 - id.length()) << "|" << endl;
  cout << "| Password :                                |" << endl;
  cin >> password;
  cout << "| Entered Your Password : " << password
       << setw(22 - password.length()) << "|" << endl;
  if (user.verifyLogin(id, password)) {
    cout << "| Sign in successfully!                     |" << endl;
    cout << "|                                           |" << endl;
    cout << "|                                           |" << endl;
    cout << "| a few seconds to move next Menu           |" << endl;

    do {
      // Countdown loop from 3 to 1
      for (int i = 3; i > 0; --i) {
        // Printing the remaining seconds
        cout << "\033[2J\033[1;1H";
        cout << "| " << i << " seconds remaining" << setw(27) << "|" << endl;
        // Waiting for 1 second
        this_thread::sleep_for(chrono::seconds(1));
      }
      // Printing the final message
      cout << "\033[2J\033[1;1H";
      cout << "Press any key to move next Menu" << endl;
      cin >> userResponse;
    } while (userResponse.empty());
    this->displayInnerUserMenu();
  }

  else {
    cout << "| Wrong ID or Password                      |" << endl;
    cout << "| Please try again                          |" << endl;
    cout << "|                                           |" << endl;
    cout << "|                                           |" << endl;
    cout << "|                                           |" << endl;
    cout << "|                                           |" << endl;
    this->displayOuterUserMenu();
  }
  return true;
}

// using setw() to align the messages
void ConsoleView::displayAdminInfo() {
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
       << "Name" << "|" << setw(PW_WIDTH) << right << "Password" << "|" << endl;
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
}

// messages to be alligned center
// Information could be filled with specific customer's cart
// using setw() to align the messages
void ConsoleView::displayCartInfo(ShoppingCart *cart) {
  cout << "\033[2J\033[1;1H";
  cout << "+++++++++++++++++++++++++++++++++++++++++++++" << endl;
  cout << "|                Cart Info                  |" << endl;
  cout << "|                                           |" << endl;
  cout << "+++++++++++++++++++++++++++++++++++++++++++++" << endl;
  cout << "|                                           |" << endl;
  cout << "| Plays Name :                              |" << endl;
  cout << "| Plays Location :                          |" << endl;
  cout << "| Plays Date :                              |" << endl;
  cout << "| Plays Time :                              |" << endl;
  cout << "| Quantity :                                |" << endl;
  cout << "| Total Price :                             |" << endl;
  cout << "|                                           |" << endl;
  cout << "+++++++++++++++++++++++++++++++++++++++++++++" << endl;
}

void ConsoleView::displayCustomerInfo(Customer *customer) {
  cout << "\033[2J\033[1;1H";
  cout << "+++++++++++++++++++++++++++++++++++++++++++++" << endl;
  cout << "|                Customer Info              |" << endl;
  cout << "|                                           |" << endl;
  cout << "+++++++++++++++++++++++++++++++++++++++++++++" << endl;
  cout << "|                                           |" << endl;
  cout << "| Name :                                    |" << endl;
  cout << "| Address :                                 |" << endl;
  cout << "| Credit Card Info :                        |" << endl;
  cout << "| Account Balance :                         |" << endl;
  cout << "|                                           |" << endl;
  cout << "+++++++++++++++++++++++++++++++++++++++++++++" << endl;
}

void ConsoleView::displayReservedInfo(Reserved *reserved) {
  cout << "\033[2J\033[1;1H";
  cout << "+++++++++++++++++++++++++++++++++++++++++++++" << endl;
  cout << "|                Reserved Info              |" << endl;
  cout << "|                                           |" << endl;
  cout << "+++++++++++++++++++++++++++++++++++++++++++++" << endl;
  cout << "|                                           |" << endl;
  cout << "| Play Name :                               |" << endl;
  cout << "| Play Location :                           |" << endl;
  cout << "| Play Date :                               |" << endl;
  cout << "| Play Time :                               |" << endl;
  cout << "| Seat Number :                             |" << endl;
  cout << "|                                           |" << endl;
  cout << "+++++++++++++++++++++++++++++++++++++++++++++" << endl;
}

// using setw() to align the messages
// currentPage is the current page number
// playsList is the list of plays
// it is not finished yet
// trying to understand the code when all the functions are implemented
void ConsoleView::displayPlaysInfo(const vector<Plays *> &playsList,
                                   int currentPage) {
  const int PLAYS_PER_PAGE = 4;
  const int totalPlays = playsList.size();
  const int totalPages = (totalPlays + PLAYS_PER_PAGE - 1) / PLAYS_PER_PAGE;

  if (currentPage < 1)
    currentPage = 1;
  if (currentPage > totalPages)
    currentPage = totalPages;

  int startIdx = (currentPage - 1) * PLAYS_PER_PAGE;
  int endIdx = min(startIdx + PLAYS_PER_PAGE, totalPlays);

  cout << "\033[2J\033[1;1H";
  cout << "+++++++++++++++++++++++++++++++++++++++++++++" << endl;
  cout << "|                Plays List                  |" << endl;
  cout << "|                                           |" << endl;
  cout << "+++++++++++++++++++++++++++++++++++++++++++++" << endl;

  for (int i = startIdx; i < endIdx; i++) {
    Plays *play = playsList[i];
    cout << "|-------------------------------------------|" << endl;
    cout << "| Play ID: " << setw(33) << left << play->getId() << "|" << endl;
    cout << "| Name: " << setw(35) << left << play->getName() << "|" << endl;
    cout << "| Location: " << setw(32) << left << play->getLocation() << "|"
         << endl;
    cout << "| Date: " << setw(35) << left << play->getDate() << "|" << endl;
    cout << "| Time: " << setw(35) << left << play->getTime() << "|" << endl;
    cout << "|-------------------------------------------|" << endl;
  }

  cout << "|                                           |" << endl;
  cout << "| Page " << currentPage << " of " << totalPages;
  cout << setw(28) << right << "|" << endl;
  cout << "| [P]rev  [N]ext  [B]ack to Menu           |" << endl;
  cout << "+++++++++++++++++++++++++++++++++++++++++++++" << endl;

  char choice;
  cout << "Enter your choice: ";
  cin >> choice;

  switch (tolower(choice)) {
  case 'p':
    if (currentPage > 1) {
      displayPlaysInfo(playsList, currentPage - 1);
    }
    break;
  case 'n':
    if (currentPage < totalPages) {
      displayPlaysInfo(playsList, currentPage + 1);
    }
    break;
  case 'b':
    displayPlaysMenu();
    return;
  default:
    displayPlaysInfo(playsList, currentPage);
    break;
  }
}

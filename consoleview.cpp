#include "consoleview.h"
#include "customermanager.h"
#include "filehandler.h"
#include "logincontroller.h"
#include "playsmanager.h"

#include "shoppingcartmanager.h"
#include <chrono>
#include <iomanip>
#include <iostream>
#include <string>
#include <thread>
#include <vector>

using namespace std;

ConsoleView::ConsoleView() { loginManager = new LoginAccountManager(); }

ConsoleView::~ConsoleView() { delete loginManager; }

bool ConsoleView::displayMainMenu() {
  int ch;
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
    displayLogin();
    break;
  case 2:
    displayAccountRegisterMenu();
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
  cout << "|2. Remove Cart                             |" << endl;
  cout << "|3. Modify Cart                             |" << endl;
  cout << "|4. View My Cart                            |" << endl;
  cout << "|5. Search Cart                             |" << endl;
  cout << "|6. Pay Cart                                |" << endl;
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
    shoppingCartManager.removeCart(customerId);
    break;
  case 3:
    shoppingCartManager.modifyCart(customerId);
    break;
  case 4:
    shoppingCartManager.viewCart(nullptr);
    break;
  case 5:
    shoppingCartManager.searchCart(customerId);
    break;
  case 6:
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
  Reserved reserved;
  int reservedId = reserved.getReservedId();
  int customerId = 0; // 임시로 0으로 설정
  ReservedManager reservedManager;
  cout << "\033[2J\033[1;1H";
  cout << "+++++++++++++++++++++++++++++++++++++++++++++" << endl;
  cout << "|                Reserved Menu              |" << endl;
  cout << "|                                           |" << endl;
  cout << "+++++++++++++++++++++++++++++++++++++++++++++" << endl;
  cout << "|1. Add Reserved                            |" << endl;
  cout << "|2. Cancel Reserved                         |" << endl;
  cout << "|3. Modify Reserved                         |" << endl;
  cout << "|4. Search Reserved Info                    |" << endl;
  cout << "|5. View My Reserved                        |" << endl;
  cout << "|                                           |" << endl;
  cout << "|                                           |" << endl;
  cout << "|9. Back to Default Menu                    |" << endl;
  cout << "|0. Quit this program                       |" << endl;
  cout << "+++++++++++++++++++++++++++++++++++++++++++++" << endl;
  cin >> ch;
  switch (ch) {
  case 1:
    reservedManager.addReserved(customerId, 0, 1, 0.0f); // 임시 값으로 설정
    break;
  case 2:
    reservedManager.cancelReserved(reservedId);
    break;
  case 3:
    reservedManager.modifyReserved(reservedId, vector<int>{}); // 빈 좌석 목록
    break;
  case 4:
    reservedManager.searchReserved(reservedId);
    break;
  case 5:
    reservedManager.viewMyReserved(customerId);
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
  cout << "\033[2J\033[1;1H";
  cout << "+++++++++++++++++++++++++++++++++++++++++++++" << endl;
  cout << "|           Account Register Menu           |" << endl;
  cout << "|                                           |" << endl;
  cout << "+++++++++++++++++++++++++++++++++++++++++++++" << endl;

  string id, password, userType = "customer";
  cout << "| ID를 입력하세요: ";
  cin >> id;
  cout << "| 비밀번호를 입력하세요: ";
  cin >> password;

  if (loginManager->createAccount(id, password, userType)) {
    cout << "| 계정이 성공적으로 생성되었습니다.          |" << endl;
    cout << "| 로그인 화면으로 이동합니다.               |" << endl;
    this_thread::sleep_for(chrono::seconds(2));
    return displayLogin();
  } else {
    cout << "| 계정 생성에 실패했습니다.                 |" << endl;
    cout << "| 메인 메뉴로 돌아갑니다.                  |" << endl;
    this_thread::sleep_for(chrono::seconds(2));
    return displayMainMenu();
  }
}

bool ConsoleView::displayLogin() {
  string id, password;
  cout << "\033[2J\033[1;1H";
  cout << "+++++++++++++++++++++++++++++++++++++++++++++" << endl;
  cout << "|                Login                      |" << endl;
  cout << "|                                           |" << endl;
  cout << "+++++++++++++++++++++++++++++++++++++++++++++" << endl;
  cout << "| ID: ";
  cin >> id;
  cout << "| Password: ";
  cin >> password;

  if (loginManager->isAccountLocked(id)) {
    cout << "| 계정이 잠겼습니다. 관리자에게 문의하세요.    |" << endl;
    this_thread::sleep_for(chrono::seconds(2));
    return displayMainMenu();
  }

  User *user = loginManager->verifyLogin(id, password);
  if (user) {
    cout << "| 로그인 성공!                             |" << endl;
    this_thread::sleep_for(chrono::seconds(1));

    if (user->getUserType() == "admin") {
      return displayAdminMenu();
    } else {
      return displayUserDashboard();
    }
  }

  cout << "| 로그인 실패                               |" << endl;
  this_thread::sleep_for(chrono::seconds(2));
  return displayMainMenu();
}

bool ConsoleView::displayUserDashboard() {
  int ch;
  cout << "\033[2J\033[1;1H";
  cout << "+++++++++++++++++++++++++++++++++++++++++++++" << endl;
  cout << "|              User Dashboard               |" << endl;
  cout << "|                                           |" << endl;
  cout << "+++++++++++++++++++++++++++++++++++++++++++++" << endl;
  cout << "|1. Goto Cart Menu                          |" << endl;
  cout << "|2. Goto Personal Menu                      |" << endl;
  cout << "|3. Goto Plays Menu                         |" << endl;
  cout << "|4. Goto Reserved Menu                      |" << endl;
  cout << "|5. Logout                                  |" << endl;
  cout << "|                                           |" << endl;
  cout << "|0. Quit this program                       |" << endl;
  cout << "+++++++++++++++++++++++++++++++++++++++++++++" << endl;
  cin >> ch;
  switch (ch) {
  case 1:
    displayCartMenu();
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
  default:
    displayUserDashboard();
    break;
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
    cout << "| Play ID: " << setw(33) << left << play->getPlaysId() << "|"
         << endl;
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

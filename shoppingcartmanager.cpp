#include "shoppingcartmanager.h"
#include <iostream>
#include <stdexcept>
// #include <fstream>
// #include <sstream>

using namespace std;

ShoppingCartManager::ShoppingCartManager() {
  playsManager = new PlaysManager();
  reservedManager = new ReservedManager();
  seatManager = new SeatManager();
  loadFromDatabase(); // 시작시 데이터 로드
}

ShoppingCartManager::~ShoppingCartManager() {
  saveToDatabase(); // 종료시 데이터 저장
  clearCarts();
  delete playsManager;
  delete reservedManager;
  delete seatManager;
}

void ShoppingCartManager::clearCarts() {
  for (auto &pair : carts) {
    delete pair.second;
  }
  carts.clear();
}

bool ShoppingCartManager::addCart(int customerId, int playId, int quantity) {
  try {
    // 공연 존재 여부 확인
    Plays *play = playsManager->searchPlays(playId);
    if (!play) {
      throw runtime_error("해당 공연이 존재하지 않습니다.");
    }

    // 이미 장바구니가 있는지 확인
    if (findCart(customerId)) {
      throw runtime_error("이미 장바구니에 다른 공연이 있습니다.");
    }

    // 새 장바구니 생성
    unique_ptr<ShoppingCart> tempCart(new ShoppingCart(customerId));
    tempCart->setPlayId(playId);
    tempCart->setQuantity(quantity);
    tempCart->setPricePerSeat(play->getPrice());

    if (!tempCart->validateCart()) {
      throw runtime_error("장바구니 생성 중 유효성 검사 실패");
    }

    carts[customerId] = tempCart.release();

    if (saveToDatabase()) {
      cout << "장바구니에 추가되었습니다." << endl;
      cout << "총 가격: " << carts[customerId]->getFormattedTotalPrice() << "원"
           << endl;
      return true;
    }

    // 저장 실패 시 메모리 정리
    delete carts[customerId];
    carts.erase(customerId);
    throw runtime_error("장바구니 저장 중 오류가 발생했습니다.");
  } catch (const exception &e) {
    cout << "오류: " << e.what() << endl;
    return false;
  }
}

bool ShoppingCartManager::removeCart(int customerId) {
  auto it = carts.find(customerId);
  if (it != carts.end()) {
    delete it->second;
    carts.erase(it);
    if (saveToDatabase()) {
      cout << "장바구니가 삭제되었습니다." << endl;
      return true;
    }
    cout << "장바구니 삭제 중 오류가 발생했습니다." << endl;
  }
  return false;
}

bool ShoppingCartManager::modifyCart(int customerId, int quantity) {
  ShoppingCart *cart = findCart(customerId);
  if (!cart) {
    cout << "장바구니가 존재하지 않습니다." << endl;
    return false;
  }

  if (quantity <= 0) {
    cout << "수량은 1개 이상이어야 합니다." << endl;
    return false;
  }

  cart->setQuantity(quantity);
  cout << "수량이 수정되었습니다." << endl;
  return saveToDatabase();
}

void ShoppingCartManager::viewCart(int customerId) {
  ShoppingCart *cart = findCart(customerId);
  if (!cart) {
    cout << "장바구니가 비어있습니다." << endl;
    return;
  }

  try {
    if (!cart->validateCart()) {
      throw runtime_error("장바구니 유효성 검사 실패");
    }

    Plays *play = playsManager->searchPlays(cart->getPlayId());
    if (!play) {
      throw runtime_error("공연 정보를 찾을 수 없습니다.");
    }

    cout << "\n장바구니 정보:" << endl;
    cout << "공연 ID: " << play->getPlaysId() << endl;
    cout << "공연명: " << play->getName() << endl;
    cout << "공연 날짜: " << play->getDate() << endl;
    cout << "공연 시간: " << play->getTime() << endl;
    cout << "공연장: " << play->getLocation() << endl;
    cout << "수량: " << cart->getQuantity() << "매" << endl;
    cout << "좌석당 가격: " << play->getPrice() << "원" << endl;
    cout << "총 가격: " << cart->getFormattedTotalPrice() << "원" << endl;
    cout << "상태: "
         << (cart->getStatus() == CartStatus::PENDING ? "대기중" : "확정됨")
         << endl;
  } catch (const exception &e) {
    cout << "오류: " << e.what() << endl;
  }
}

ShoppingCart *ShoppingCartManager::findCart(int customerId) {
  auto it = carts.find(customerId);
  return (it != carts.end()) ? it->second : nullptr;
}

bool ShoppingCartManager::pay(Customer *customer) {
  if (!customer) {
    cout << "고객 정보가 없습니다." << endl;
    return false;
  }

  ShoppingCart *cart = findCart(customer->getId());
  if (!cart) {
    cout << "장바구니가 비어있습니다." << endl;
    return false;
  }

  try {
    if (!cart->validateCart()) {
      throw runtime_error("장바구니 유효성 검사 실패");
    }

    Plays *play = playsManager->searchPlays(cart->getPlayId());
    if (!play) {
      throw runtime_error("공연 정보를 찾을 수 없습니다.");
    }

    float totalAmount = cart->getTotalPrice();

    // 1. 좌석 임시 예약
    vector<int> seats =
        seatManager->preReserveSeats(play->getPlaysId(), cart->getQuantity());
    if (seats.empty()) {
      throw runtime_error("예약 가능한 좌석이 부족합니다.");
    }

    // 2. 결제 처리
    if (!processPayment(customer, totalAmount)) {
      seatManager->releaseSeats(play->getPlaysId(), seats);
      throw runtime_error("결제에 실패했습니다.");
    }

    // 3. 예약 정보 생성
    if (!reservedManager->addReserved(customer->getId(), play->getPlaysId(),
                                      cart->getQuantity(), totalAmount)) {
      // 롤백 처리
      seatManager->releaseSeats(play->getPlaysId(), seats);
      refundPayment(customer, totalAmount);
      throw runtime_error("예약 처리 중 오류가 발생했습니다.");
    }

    // 4. 좌석 예약 확정
    if (!seatManager->confirmReservation(play->getPlaysId(), seats)) {
      throw runtime_error("좌석 예약 확정 실패");
    }

    // 5. 장바구니 상태 업데이트 및 삭제
    cart->setStatus(CartStatus::CONFIRMED);

    cout << "결제가 완료되었습니다." << endl;
    cout << "결제 금액: " << cart->getFormattedTotalPrice() << "원" << endl;
    cout << "예약된 좌석 번호: ";
    for (int seat : seats) {
      cout << seat << " ";
    }
    cout << endl;
    cout << "남은 잔액: " << customer->getAccountBalance() << "원" << endl;

    removeCart(customer->getId());
    return true;
  } catch (const exception &e) {
    cout << "오류: " << e.what() << endl;
    return false;
  }
}

bool ShoppingCartManager::processPayment(Customer *customer, float amount) {
  if (customer->getAccountBalance() >= amount) {
    customer->withdraw(amount);
    return true;
  }
  return false;
}

void ShoppingCartManager::refundPayment(Customer *customer, float amount) {
  customer->deposit(amount);
  cout << "결제가 취소되어 " << amount << "원이 환불되었습니다." << endl;
}

bool ShoppingCartManager::saveToDatabase() {
  try {
    vector<vector<string>> data;
    data.push_back({"CustomerID", "PlayID", "Quantity", "PricePerSeat",
                    "TotalPrice", "Status"});

    for (const auto &pair : carts) {
      const ShoppingCart *cart = pair.second;
      vector<string> row;

      row.push_back(to_string(cart->getCustomerId()));
      row.push_back(to_string(cart->getPlayId()));
      row.push_back(to_string(cart->getQuantity()));
      row.push_back(to_string(cart->getPricePerSeat()));
      row.push_back(to_string(cart->getTotalPrice()));
      row.push_back(cart->getStatus() == CartStatus::PENDING ? "PENDING"
                                                             : "CONFIRMED");

      data.push_back(row);
    }

    return fileHandler.writeCSV("sources/shopping_carts.csv", data);
  } catch (const exception &e) {
    cout << "장바구니 저장 중 오류 발생: " << e.what() << endl;
    return false;
  }
}

bool ShoppingCartManager::loadFromDatabase() {
  try {
    string filename = "sources/shopping_carts.csv";
    vector<vector<string>> data = fileHandler.readCSV(filename);

    clearCarts(); // 기존 데이터 정리

    // 데이터가 비어있거나 헤더만 있는 경우
    if (data.size() <= 1) {
      return true;
    }

    for (size_t i = 1; i < data.size(); i++) { // 첫 줄은 헤더
      const vector<string> &row = data[i];
      if (row.size() >= 6) {
        int customerId = stoi(row[0]);
        ShoppingCart *cart = new ShoppingCart(customerId);
        cart->setPlayId(stoi(row[1]));
        cart->setQuantity(stoi(row[2]));
        cart->setPricePerSeat(stof(row[3]));
        cart->setStatus(row[5] == "PENDING" ? CartStatus::PENDING
                                            : CartStatus::CONFIRMED);

        carts[customerId] = cart;
      }
    }
    return true;
  } catch (const exception &e) {
    cout << "장바구니 로드 중 오류 발생: " << e.what() << endl;
    return false;
  }
}

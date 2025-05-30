#ifndef SHOPPINGCARTMANAGER_H
#define SHOPPINGCARTMANAGER_H

#include "customer.h"
#include "filehandler.h"
#include "playsmanager.h"
#include "reservedmanager.h"
#include "seatmanager.h"
#include "shoppingcart.h"
#include <map>
#include <vector>

// #include "user.h"

class ShoppingCartManager {
public:
  ShoppingCartManager();
  ~ShoppingCartManager();

  bool addCart(int customerId, int playId, int quantity);
  bool removeCart(int customerId);
  bool modifyCart(int customerId, int quantity);
  void viewCart(int customerId);
  ShoppingCart *findCart(int customerId);
  bool pay(Customer *customer);

private:
  map<int, ShoppingCart *> carts;
  PlaysManager *playsManager;
  ReservedManager *reservedManager;
  SeatManager *seatManager;
  FileHandler fileHandler;

  bool processPayment(Customer *customer, float amount);
  void refundPayment(Customer *customer, float amount);

  // 데이터베이스 관련 함수
  bool saveToDatabase();
  bool loadFromDatabase();
  void clearCarts(); // 모든 장바구니 삭제
};
#endif // SHOPPINGCARTMANAGER_H

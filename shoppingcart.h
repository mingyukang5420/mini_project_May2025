#ifndef SHOPPINGCART_H
#define SHOPPINGCART_H

#include "plays.h"
#include "user.h"
#include <map>

class ShoppingCart {
public:
  ShoppingCart();
  ~ShoppingCart();

  int getPlayId();
  int getQuantity();
  float getTotalPrice();
  void updateQuantity(int);

private:
  map<int, Plays *> cartList;
  int customerId;
  int playId;
  int quantity;
  float totalPrice;
};
#endif // SHOPPINGCART_H

#ifndef SHOPPINGCARTMANAGER_H
#define SHOPPINGCARTMANAGER_H

#include "customer.h"
#include "shoppingcart.h"

// #include "user.h"

class ShoppingCartManager {
public:
  ShoppingCartManager();
  ~ShoppingCartManager();

  void addCart();
  void cancelCart(int customerId);
  void removeCart(int customerId);
  void modifyCart(int customerId);
  void viewCart(ShoppingCart *cart);
  ShoppingCart *searchCart(int customerId);
  void pay(Customer *customer);
};
#endif // SHOPPINGCARTMANAGER_H

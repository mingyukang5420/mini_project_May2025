#ifndef SHOPPINGCART_H
#define SHOPPINGCART_H

#include <iomanip>
#include <sstream>
#include <string>

using namespace std;

// 장바구니 상태를 enum class로 정의
enum class CartStatus { PENDING, CONFIRMED };

class ShoppingCart {
private:
  int customerId;
  int playId;
  CartStatus status;
  string seatNumber;
  int quantity;
  float pricePerSeat;
  float totalPrice;

public:
  explicit ShoppingCart(int customerId = 0);
  ~ShoppingCart() = default;

  // Getters
  int getCustomerId() const { return customerId; }
  int getPlayId() const { return playId; }
  int getQuantity() const { return quantity; }
  float getPricePerSeat() const { return pricePerSeat; }
  float getTotalPrice() const { return totalPrice; }
  string getFormattedTotalPrice() const {
    stringstream ss;
    ss << fixed << setprecision(0) << totalPrice;
    return ss.str();
  }
  CartStatus getStatus() const { return status; }
  string getSeatNumber() const { return seatNumber; }

  // Setters
  void setPlayId(int id) { playId = id; }
  void setQuantity(int qty) {
    quantity = qty;
    updateTotalPrice();
  }
  void setPricePerSeat(float price) {
    pricePerSeat = price;
    updateTotalPrice();
  }
  void setStatus(CartStatus newStatus) {
    if (canTransitionToStatus(newStatus)) {
      status = newStatus;
    }
  }
  void setSeatNumber(const string &seat) { seatNumber = seat; }

  // 상태 관리
  bool canTransitionToStatus(CartStatus newStatus) const {
    return status == CartStatus::PENDING && newStatus == CartStatus::CONFIRMED;
  }

  // 유효성 검사
  bool validateCart() const {
    return !isEmpty() && customerId > 0 && quantity > 0 && pricePerSeat > 0;
  }

  // 상태 확인
  bool isEmpty() const { return playId == 0; }

private:
  void updateTotalPrice() { totalPrice = quantity * pricePerSeat; }
};

#endif

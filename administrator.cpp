#include "administrator.h"
#include "customermanager.h"
#include "playsmanager.h"
#include "reservedmanager.h"
#include <iostream>

using namespace std;

Administrator::Administrator() : m_adminId(0), m_adminName("") {
  setUserType("admin");
}

Administrator::~Administrator() {
  // 민감한 정보 초기화
  m_adminName.clear();
}

bool Administrator::verifyAdminPrivileges() const {
  return getUserType() == "admin";
}

bool Administrator::addPlay(const Plays &play) {
  if (!verifyAdminPrivileges()) {
    cout << "권한이 없습니다." << endl;
    return false;
  }

  PlaysManager playsManager;
  playsManager.addPlays(); // void 반환형이므로 성공 여부를 알 수 없음
  return true;             // 항상 성공으로 처리
}

bool Administrator::modifyPlay(int playId, const Plays &updatedPlay) {
  if (!verifyAdminPrivileges()) {
    cout << "권한이 없습니다." << endl;
    return false;
  }

  PlaysManager playsManager;
  playsManager.modifyPlays(playId, this); // this를 User*로 전달
  return true;
}

bool Administrator::removePlay(int playId) {
  if (!verifyAdminPrivileges()) {
    cout << "권한이 없습니다." << endl;
    return false;
  }

  PlaysManager playsManager;
  playsManager.removePlays(playId, this);
  return true;
}

vector<Plays> Administrator::listAllPlays() const {
  if (!verifyAdminPrivileges()) {
    cout << "권한이 없습니다." << endl;
    return vector<Plays>();
  }

  vector<Plays> result;
  PlaysManager playsManager;
  playsManager.viewPlays(); // 실제로는 콘솔에 출력만 함
  return result;            // 빈 벡터 반환
}

bool Administrator::viewCustomerInfo(int customerId) const {
  if (!verifyAdminPrivileges()) {
    cout << "권한이 없습니다." << endl;
    return false;
  }

  CustomerManager customerManager;
  Customer *customer = customerManager.searchCustomer(customerId);
  if (customer) {
    cout << "고객 정보:" << endl;
    cout << "ID: " << customer->getId() << endl;
    cout << "이름: " << customer->getCustomerName() << endl;
    cout << "주소: " << customer->getAddress() << endl;
    cout << "전화번호: " << customer->getPhoneNumber() << endl;
    cout << "가입일: " << customer->getRegisterDate() << endl;
    return true;
  }
  return false;
}

bool Administrator::modifyCustomerInfo(int customerId,
                                       const Customer &updatedInfo) {
  if (!verifyAdminPrivileges()) {
    cout << "권한이 없습니다." << endl;
    return false;
  }

  CustomerManager customerManager;
  customerManager.modifyCustomer(customerId, this);
  return true;
}

bool Administrator::removeCustomer(int customerId) {
  if (!verifyAdminPrivileges()) {
    cout << "권한이 없습니다." << endl;
    return false;
  }

  CustomerManager customerManager;
  customerManager.removeCustomer(customerId, this);
  return true;
}

vector<Customer> Administrator::listAllCustomers() const {
  if (!verifyAdminPrivileges()) {
    cout << "권한이 없습니다." << endl;
    return vector<Customer>();
  }

  vector<Customer> result;
  // 현재 CustomerManager에는 모든 고객을 반환하는 메서드가 없음
  return result;
}

bool Administrator::viewReservation(int reservationId) const {
  if (!verifyAdminPrivileges()) {
    cout << "권한이 없습니다." << endl;
    return false;
  }

  ReservedManager reservedManager;
  Reserved *reservation = reservedManager.searchReserved(reservationId);
  if (reservation) {
    cout << "예약 정보:" << endl;
    cout << "예약 ID: " << reservation->getReservedId() << endl;
    cout << "공연 ID: " << reservation->getReservedPlaysId() << endl;
    cout << "고객 ID: " << reservation->getReservedCustomerId() << endl;
    cout << "예약 날짜: " << reservation->getReservedDate() << endl;
    cout << "예약 좌석: ";
    for (const auto &seat : reservation->getReservedSeats()) {
      cout << seat << " ";
    }
    cout << endl;
    cout << "결제 금액: " << reservation->getReservedPrice() << endl;
    cout << "상태: " << reservation->getReservedStatus() << endl;
    return true;
  }
  return false;
}

bool Administrator::cancelReservation(int reservationId) {
  if (!verifyAdminPrivileges()) {
    cout << "권한이 없습니다." << endl;
    return false;
  }

  ReservedManager reservedManager;
  reservedManager.cancelReserved(reservationId);
  return true;
}

vector<Reserved> Administrator::listAllReservations() const {
  if (!verifyAdminPrivileges()) {
    cout << "권한이 없습니다." << endl;
    return vector<Reserved>();
  }

  vector<Reserved> result;
  // 현재 ReservedManager에는 모든 예약을 반환하는 메서드가 없음
  return result;
}

vector<Reserved>
Administrator::getReservationsByCustomer(int customerId) const {
  if (!verifyAdminPrivileges()) {
    cout << "권한이 없습니다." << endl;
    return vector<Reserved>();
  }

  vector<Reserved> result;
  // 현재 ReservedManager에는 고객별 예약을 반환하는 메서드가 없음
  return result;
}

vector<Reserved> Administrator::getReservationsByPlay(int playId) const {
  if (!verifyAdminPrivileges()) {
    cout << "권한이 없습니다." << endl;
    return vector<Reserved>();
  }

  vector<Reserved> result;
  // 현재 ReservedManager에는 공연별 예약을 반환하는 메서드가 없음
  return result;
}

float Administrator::calculateTotalRevenue() const {
  if (!verifyAdminPrivileges()) {
    cout << "권한이 없습니다." << endl;
    return 0.0f;
  }

  float totalRevenue = 0.0f;
  // 현재는 구현할 수 없음 - ReservedManager에 필요한 메서드가 없음
  return totalRevenue;
}

int Administrator::getTotalCustomers() const {
  if (!verifyAdminPrivileges()) {
    cout << "권한이 없습니다." << endl;
    return 0;
  }

  // 현재는 구현할 수 없음 - CustomerManager에 필요한 메서드가 없음
  return 0;
}

int Administrator::getTotalReservations() const {
  if (!verifyAdminPrivileges()) {
    cout << "권한이 없습니다." << endl;
    return 0;
  }

  // 현재는 구현할 수 없음 - ReservedManager에 필요한 메서드가 없음
  return 0;
}

vector<pair<int, int>> Administrator::getMostPopularPlays() const {
  if (!verifyAdminPrivileges()) {
    cout << "권한이 없습니다." << endl;
    return vector<pair<int, int>>();
  }

  // 현재는 구현할 수 없음 - ReservedManager에 필요한 메서드가 없음
  return vector<pair<int, int>>();
}

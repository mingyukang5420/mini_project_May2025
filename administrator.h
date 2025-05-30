#ifndef ADMINISTRATOR_H
#define ADMINISTRATOR_H

#include "customer.h"
#include "plays.h"
#include "reserved.h"
#include "user.h"
#include <vector>

class Administrator : public User {
public:
  Administrator();
  ~Administrator() override;

  // Getters
  int getAdminId() const { return m_adminId; }
  string getAdminName() const { return m_adminName; }

  // Setters
  void setAdminId(int id) { m_adminId = id; }
  void setAdminName(const string &name) { m_adminName = name; }

  // 관리자 특권 기능
  bool addPlay(const Plays &play);
  bool modifyPlay(int playId, const Plays &updatedPlay);
  bool removePlay(int playId);
  vector<Plays> listAllPlays() const;

  bool viewCustomerInfo(int customerId) const;
  bool modifyCustomerInfo(int customerId, const Customer &updatedInfo);
  bool removeCustomer(int customerId);
  vector<Customer> listAllCustomers() const;

  bool viewReservation(int reservationId) const;
  bool cancelReservation(int reservationId);
  vector<Reserved> listAllReservations() const;
  vector<Reserved> getReservationsByCustomer(int customerId) const;
  vector<Reserved> getReservationsByPlay(int playId) const;

  // 통계 및 보고서
  float calculateTotalRevenue() const;
  int getTotalCustomers() const;
  int getTotalReservations() const;
  vector<pair<int, int>>
  getMostPopularPlays() const; // <playId, reservationCount>

private:
  int m_adminId;
  string m_adminName;

  // 권한 검증
  bool verifyAdminPrivileges() const;
};

#endif // ADMINISTRATOR_H

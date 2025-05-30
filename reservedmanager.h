#ifndef RESERVEDMANAGER_H
#define RESERVEDMANAGER_H

#include "filehandler.h"
#include "reserved.h"
#include <functional>
#include <map>
#include <string>
#include <vector>

using namespace std;

class ReservedManager {
public:
  ReservedManager();
  ~ReservedManager();

  // 예약 추가 및 관리
  bool addReserved(int customerId, int playId, int quantity, float totalPrice);
  bool addReservedWithSeats(int customerId, int playId,
                            const vector<int> &seats, float totalPrice);
  bool cancelReserved(int reservedId);
  bool modifyReserved(int reservedId, const vector<int> &newSeats);

  // 예약 조회
  void viewMyReserved(int customerId);
  void viewAllReserved();
  Reserved *searchReserved(int reservedId);

  // 고급 예약 조회 기능
  vector<Reserved *> getAllReservations() const;
  vector<Reserved *> getReservationsByCustomer(int customerId) const;
  vector<Reserved *> getReservationsByPlay(int playId) const;
  vector<Reserved *> getReservationsByStatus(const string &status) const;
  vector<Reserved *> getReservationsByDateRange(time_t startDate,
                                                time_t endDate) const;

  // 통계 및 분석
  int getTotalReservationCount() const;
  int getCustomerReservationCount(int customerId) const;
  int getPlayReservationCount(int playId) const;
  float getTotalRevenue() const;
  float getPlayRevenue(int playId) const;
  map<int, int> getPlayPopularityRanking() const; // <playId, reservationCount>

  // 예약 상태 관리
  bool confirmReserved(int reservedId);
  bool refundReserved(int reservedId);

private:
  map<int, Reserved *> reservationList;
  FileHandler fileHandler;

  // 유틸리티 함수
  int generateReservationId();
  bool saveToDatabase();
  bool loadFromDatabase();
  bool isValidSeat(int playId, const vector<int> &seats);

  // 내부 헬퍼 함수
  vector<Reserved *>
  filterReservations(const function<bool(const Reserved *)> &predicate) const;
};

#endif // RESERVEDMANAGER_H

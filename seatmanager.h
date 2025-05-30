#ifndef SEATMANAGER_H
#define SEATMANAGER_H

#include <bitset>
#include <map>
#include <set>
#include <unordered_map>
#include <vector>

using namespace std;

class SeatManager {
public:
  SeatManager();
  ~SeatManager();

  // 좌석 예약 관련
  vector<int> preReserveSeats(int playId, int quantity);
  bool confirmReservation(int playId, const vector<int> &seats);
  void releaseSeats(int playId, const vector<int> &seats);
  bool isValidSeat(int playId, const vector<int> &seats);

  // 좌석 상태 조회
  bool isSeatAvailable(int playId, int seatNumber);
  vector<int> getAvailableSeats(int playId);
  int getAvailableSeatCount(int playId);

  // 좌석 초기화
  void initializeSeats(int playId, int totalSeats);
  void clearPlaySeats(int playId);

private:
  // 비트맵을 사용한 좌석 관리 (64개 좌석을 1바이트로 관리)
  map<int, vector<bitset<64>>> seatBitmap; // playId -> 좌석 비트맵

  // 임시 예약 관리
  map<int, set<int>> tempReservedSeats; // playId -> 임시 예약된 좌석 집합

  // 좌석 캐싱
  unordered_map<int, vector<int>> seatCache; // 자주 사용되는 좌석 조합

  // 유틸리티 함수
  vector<int> findConsecutiveSeats(int playId, int quantity);
  void updateSeatBitmap(int playId, int seatNumber, bool isReserved);
  bool isValidSeatRange(int playId, int seatNumber);
};

#endif // SEATMANAGER_H
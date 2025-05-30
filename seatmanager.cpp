#include "seatmanager.h"
// #include <iostream>

SeatManager::SeatManager() {}

SeatManager::~SeatManager() {
  // 모든 임시 예약 해제
  tempReservedSeats.clear();
  // 캐시 정리
  seatCache.clear();
}

vector<int> SeatManager::preReserveSeats(int playId, int quantity) {
  // 캐시된 좌석 조합이 있는지 확인
  auto cacheIt = seatCache.find(playId);
  if (cacheIt != seatCache.end() && cacheIt->second.size() >= quantity) {
    vector<int> seats(cacheIt->second.begin(),
                      cacheIt->second.begin() + quantity);
    // 캐시에서 사용한 좌석 제거
    cacheIt->second.erase(cacheIt->second.begin(),
                          cacheIt->second.begin() + quantity);
    return seats;
  }

  // 연속된 좌석 찾기
  vector<int> seats = findConsecutiveSeats(playId, quantity);
  if (seats.empty()) {
    return seats; // 실패
  }

  // 임시 예약에 추가
  for (int seat : seats) {
    tempReservedSeats[playId].insert(seat);
    updateSeatBitmap(playId, seat, true);
  }

  return seats;
}

bool SeatManager::confirmReservation(int playId, const vector<int> &seats) {
  // 모든 좌석이 임시 예약 상태인지 확인
  for (int seat : seats) {
    if (tempReservedSeats[playId].find(seat) ==
        tempReservedSeats[playId].end()) {
      return false;
    }
  }

  // 임시 예약에서 제거 (이미 비트맵에는 예약된 상태)
  for (int seat : seats) {
    tempReservedSeats[playId].erase(seat);
  }

  return true;
}

void SeatManager::releaseSeats(int playId, const vector<int> &seats) {
  for (int seat : seats) {
    // 임시 예약에서 제거
    tempReservedSeats[playId].erase(seat);
    // 비트맵에서 해제
    updateSeatBitmap(playId, seat, false);
    // 캐시에 추가
    seatCache[playId].push_back(seat);
  }
}

bool SeatManager::isValidSeat(int playId, const vector<int> &seats) {
  for (int seat : seats) {
    if (!isValidSeatRange(playId, seat)) {
      return false;
    }
  }
  return true;
}

bool SeatManager::isSeatAvailable(int playId, int seatNumber) {
  if (!isValidSeatRange(playId, seatNumber)) {
    return false;
  }

  // 비트맵에서 확인
  int blockIndex = seatNumber / 64;
  int bitIndex = seatNumber % 64;
  return !seatBitmap[playId][blockIndex].test(bitIndex);
}

vector<int> SeatManager::getAvailableSeats(int playId) {
  vector<int> available;
  if (seatBitmap.find(playId) == seatBitmap.end()) {
    return available;
  }

  for (size_t block = 0; block < seatBitmap[playId].size(); ++block) {
    for (size_t bit = 0; bit < 64; ++bit) {
      if (!seatBitmap[playId][block].test(bit)) {
        int seatNumber = block * 64 + bit;
        available.push_back(seatNumber);
      }
    }
  }
  return available;
}

int SeatManager::getAvailableSeatCount(int playId) {
  if (seatBitmap.find(playId) == seatBitmap.end()) {
    return 0;
  }

  int count = 0;
  for (const auto &block : seatBitmap[playId]) {
    count += 64 - block.count(); // 비트가 0인 것이 빈 좌석
  }
  return count;
}

void SeatManager::initializeSeats(int playId, int totalSeats) {
  // 필요한 비트맵 블록 수 계산
  int numBlocks = (totalSeats + 63) / 64; // 올림 나눗셈

  // 비트맵 초기화
  seatBitmap[playId] = vector<bitset<64>>(numBlocks);

  // 임시 예약 초기화
  tempReservedSeats[playId].clear();

  // 캐시 초기화
  seatCache[playId].clear();
}

void SeatManager::clearPlaySeats(int playId) {
  seatBitmap.erase(playId);
  tempReservedSeats.erase(playId);
  seatCache.erase(playId);
}

// Private 메서드들
vector<int> SeatManager::findConsecutiveSeats(int playId, int quantity) {
  vector<int> seats;
  if (seatBitmap.find(playId) == seatBitmap.end()) {
    return seats;
  }

  for (size_t block = 0; block < seatBitmap[playId].size(); ++block) {
    for (size_t bit = 0; bit < 64; ++bit) {
      int currentSeat = block * 64 + bit;
      if (isSeatAvailable(playId, currentSeat)) {
        seats.push_back(currentSeat);
        if (seats.size() == quantity) {
          return seats;
        }
      } else {
        seats.clear();
      }
    }
  }

  // 충분한 연속 좌석을 찾지 못한 경우
  seats.clear();
  return seats;
}

void SeatManager::updateSeatBitmap(int playId, int seatNumber,
                                   bool isReserved) {
  if (!isValidSeatRange(playId, seatNumber)) {
    return;
  }

  int blockIndex = seatNumber / 64;
  int bitIndex = seatNumber % 64;

  if (isReserved) {
    seatBitmap[playId][blockIndex].set(bitIndex);
  } else {
    seatBitmap[playId][blockIndex].reset(bitIndex);
  }
}

bool SeatManager::isValidSeatRange(int playId, int seatNumber) {
  if (seatBitmap.find(playId) == seatBitmap.end()) {
    return false;
  }

  int blockIndex = seatNumber / 64;
  return blockIndex < seatBitmap[playId].size();
}
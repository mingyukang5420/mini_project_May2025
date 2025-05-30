#include "reservedmanager.h"
#include <algorithm>
#include <ctime>
#include <iomanip>
#include <iostream>
#include <sstream>

ReservedManager::ReservedManager() { loadFromDatabase(); }

ReservedManager::~ReservedManager() {
  saveToDatabase();
  for (auto &pair : reservationList) {
    delete pair.second;
  }
  reservationList.clear();
}

bool ReservedManager::addReserved(int customerId, int playId, int quantity,
                                  float totalPrice) {
  try {
    int reservedId = generateReservationId();

    Reserved *newReservation = new Reserved();
    newReservation->setReservedId(reservedId);
    newReservation->setReservedCustomerId(customerId);
    newReservation->setReservedPlaysId(playId);

    // 현재 시간 설정
    time_t now = time(0);
    newReservation->setReservedDate(now);
    newReservation->setReservedTime(now);
    newReservation->setReservedPrice(totalPrice);
    newReservation->setReservedStatus("CONFIRMED");

    // 예약 목록에 추가
    reservationList[reservedId] = newReservation;

    // 파일에 저장
    return saveToDatabase();
  } catch (const exception &e) {
    cout << "예약 처리 중 오류 발생: " << e.what() << endl;
    return false;
  }
}

bool ReservedManager::addReservedWithSeats(int customerId, int playId,
                                           const vector<int> &seats,
                                           float totalPrice) {
  if (!isValidSeat(playId, seats)) {
    cout << "유효하지 않은 좌석입니다." << endl;
    return false;
  }

  try {
    int reservedId = generateReservationId();

    Reserved *newReservation = new Reserved();
    newReservation->setReservedId(reservedId);
    newReservation->setReservedCustomerId(customerId);
    newReservation->setReservedPlaysId(playId);
    newReservation->setReservedSeats(seats);
    newReservation->setReservedPrice(totalPrice);

    time_t now = time(0);
    newReservation->setReservedDate(now);
    newReservation->setReservedTime(now);
    newReservation->setReservedStatus("CONFIRMED");

    reservationList[reservedId] = newReservation;
    return saveToDatabase();
  } catch (const exception &e) {
    cout << "좌석 예약 중 오류 발생: " << e.what() << endl;
    return false;
  }
}

void ReservedManager::viewMyReserved(int customerId) {
  cout << "\033[2J\033[1;1H";
  cout << "+++++++++++++++++++++++++++++++++++++++++++++" << endl;
  cout << "|              Reserved List                |" << endl;
  cout << "|                                           |" << endl;
  cout << "+++++++++++++++++++++++++++++++++++++++++++++" << endl;

  vector<Reserved *> customerReservations =
      getReservationsByCustomer(customerId);
  if (customerReservations.empty()) {
    cout << "| No reservations found for this customer    |" << endl;
  } else {
    for (const auto &reservation : customerReservations) {
      cout << "| Reservation ID: " << reservation->getReservedId() << endl;
      // 추가 예약 정보 출력
    }
  }
  cout << "+++++++++++++++++++++++++++++++++++++++++++++" << endl;
}

void ReservedManager::viewAllReserved() {
  cout << "\n=== 전체 예약 내역 ===" << endl;
  if (reservationList.empty()) {
    cout << "예약 내역이 없습니다." << endl;
    return;
  }

  for (const auto &pair : reservationList) {
    Reserved *reservation = pair.second;
    cout << "예약 번호: " << reservation->getReservedId() << endl;
    cout << "고객 ID: " << reservation->getReservedCustomerId() << endl;
    cout << "공연 ID: " << reservation->getReservedPlaysId() << endl;
    cout << "예약 상태: " << reservation->getReservedStatus() << endl;

    // 시간 출력 수정
    time_t date = reservation->getReservedDate();
    tm *timeinfo = localtime(&date);
    cout << "예약 날짜: " << put_time(timeinfo, "%Y-%m-%d %H:%M:%S") << endl;

    cout << "좌석 번호: ";
    for (const int &seat : reservation->getReservedSeats()) {
      cout << seat << " ";
    }
    cout << "\n가격: " << reservation->getReservedPrice() << endl;
    cout << "---------------" << endl;
  }
}

Reserved *ReservedManager::searchReserved(int reservedId) {
  auto it = reservationList.find(reservedId);
  return (it != reservationList.end()) ? it->second : nullptr;
}

bool ReservedManager::cancelReserved(int reservedId) {
  auto it = reservationList.find(reservedId);
  if (it == reservationList.end()) {
    cout << "예약을 찾을 수 없습니다." << endl;
    return false;
  }

  it->second->setReservedStatus("CANCELLED");
  return saveToDatabase();
}

bool ReservedManager::modifyReserved(int reservedId,
                                     const vector<int> &newSeats) {
  auto it = reservationList.find(reservedId);
  if (it == reservationList.end()) {
    cout << "예약을 찾을 수 없습니다." << endl;
    return false;
  }

  if (!isValidSeat(it->second->getReservedPlaysId(), newSeats)) {
    cout << "유효하지 않은 좌석입니다." << endl;
    return false;
  }

  it->second->setReservedSeats(newSeats);
  return saveToDatabase();
}

bool ReservedManager::confirmReserved(int reservedId) {
  auto it = reservationList.find(reservedId);
  if (it == reservationList.end())
    return false;

  it->second->setReservedStatus("CONFIRMED");
  return saveToDatabase();
}

bool ReservedManager::refundReserved(int reservedId) {
  auto it = reservationList.find(reservedId);
  if (it == reservationList.end())
    return false;

  it->second->setReservedStatus("REFUNDED");
  return saveToDatabase();
}

int ReservedManager::generateReservationId() {
  int maxId = 0;
  for (const auto &pair : reservationList) {
    if (pair.first > maxId) {
      maxId = pair.first;
    }
  }
  return maxId + 1;
}

bool ReservedManager::saveToDatabase() {
  try {
    vector<vector<string>> data;
    data.push_back({"ReservationID", "CustomerID", "PlayID", "Date", "Time",
                    "Status", "Seats", "Price"});

    for (const auto &pair : reservationList) {
      Reserved *reservation = pair.second;
      vector<string> row;

      row.push_back(to_string(reservation->getReservedId()));
      row.push_back(to_string(reservation->getReservedCustomerId()));
      row.push_back(to_string(reservation->getReservedPlaysId()));
      row.push_back(to_string(reservation->getReservedDate()));
      row.push_back(to_string(reservation->getReservedTime()));
      row.push_back(reservation->getReservedStatus());

      string seats;
      const vector<int> &seatList = reservation->getReservedSeats();
      for (size_t i = 0; i < seatList.size(); i++) {
        seats += to_string(seatList[i]);
        if (i < seatList.size() - 1) {
          seats += ";";
        }
      }
      row.push_back(seats);

      row.push_back(to_string(reservation->getReservedPrice()));
      data.push_back(row);
    }

    fileHandler.writeCsv("reserved.csv", data);
    return true;
  } catch (const exception &e) {
    cout << "파일 저장 중 오류 발생: " << e.what() << endl;
    return false;
  }
}

bool ReservedManager::loadFromDatabase() {
  try {
    vector<vector<string>> data = fileHandler.readCsv("reserved.csv");

    for (auto &pair : reservationList) {
      delete pair.second;
    }
    reservationList.clear();

    for (size_t i = 1; i < data.size(); i++) {
      const vector<string> &row = data[i];
      if (row.size() >= 8) {
        Reserved *reservation = new Reserved();

        reservation->setReservedId(stoi(row[0]));
        reservation->setReservedCustomerId(stoi(row[1]));
        reservation->setReservedPlaysId(stoi(row[2]));

        time_t date = stoll(row[3]);
        time_t time = stoll(row[4]);
        reservation->setReservedDate(date);
        reservation->setReservedTime(time);
        reservation->setReservedStatus(row[5]);

        string seatsStr = row[6];
        stringstream ss(seatsStr);
        string seatNum;
        vector<int> seats;
        while (getline(ss, seatNum, ';')) {
          if (!seatNum.empty()) {
            seats.push_back(stoi(seatNum));
          }
        }
        reservation->setReservedSeats(seats);

        reservation->setReservedPrice(stof(row[7]));
        reservationList[reservation->getReservedId()] = reservation;
      }
    }

    return true;
  } catch (const exception &e) {
    cout << "파일 로드 중 오류 발생: " << e.what() << endl;
    return false;
  }
}

bool ReservedManager::isValidSeat(int playId, const vector<int> &seats) {
  // TODO: 공연별 좌석 유효성 검사 로직 구현
  // 현재는 임시로 true 반환
  return true;
}

// 내부 헬퍼 함수
vector<Reserved *> ReservedManager::filterReservations(
    const function<bool(const Reserved *)> &predicate) const {
  vector<Reserved *> result;
  for (const auto &pair : reservationList) {
    if (predicate(pair.second)) {
      result.push_back(pair.second);
    }
  }
  return result;
}

// 고급 예약 조회 기능
vector<Reserved *> ReservedManager::getAllReservations() const {
  vector<Reserved *> result;
  result.reserve(reservationList.size());
  for (const auto &pair : reservationList) {
    result.push_back(pair.second);
  }
  return result;
}

vector<Reserved *>
ReservedManager::getReservationsByCustomer(int customerId) const {
  return filterReservations([customerId](const Reserved *r) {
    return r->getReservedCustomerId() == customerId;
  });
}

vector<Reserved *> ReservedManager::getReservationsByPlay(int playId) const {
  return filterReservations([playId](const Reserved *r) {
    return r->getReservedPlaysId() == playId;
  });
}

vector<Reserved *>
ReservedManager::getReservationsByStatus(const string &status) const {
  return filterReservations([&status](const Reserved *r) {
    return r->getReservedStatus() == status;
  });
}

vector<Reserved *>
ReservedManager::getReservationsByDateRange(time_t startDate,
                                            time_t endDate) const {
  return filterReservations([startDate, endDate](const Reserved *r) {
    time_t reservationDate = r->getReservedDate();
    return reservationDate >= startDate && reservationDate <= endDate;
  });
}

// 통계 및 분석
int ReservedManager::getTotalReservationCount() const {
  return reservationList.size();
}

int ReservedManager::getCustomerReservationCount(int customerId) const {
  return getReservationsByCustomer(customerId).size();
}

int ReservedManager::getPlayReservationCount(int playId) const {
  return getReservationsByPlay(playId).size();
}

float ReservedManager::getTotalRevenue() const {
  float total = 0.0f;
  for (const auto &pair : reservationList) {
    if (pair.second->getReservedStatus() != "CANCELLED" &&
        pair.second->getReservedStatus() != "REFUNDED") {
      total += pair.second->getReservedPrice();
    }
  }
  return total;
}

float ReservedManager::getPlayRevenue(int playId) const {
  float total = 0.0f;
  auto playReservations = getReservationsByPlay(playId);
  for (const auto &reservation : playReservations) {
    if (reservation->getReservedStatus() != "CANCELLED" &&
        reservation->getReservedStatus() != "REFUNDED") {
      total += reservation->getReservedPrice();
    }
  }
  return total;
}

map<int, int> ReservedManager::getPlayPopularityRanking() const {
  map<int, int> ranking;
  for (const auto &pair : reservationList) {
    const Reserved *reservation = pair.second;
    if (reservation->getReservedStatus() != "CANCELLED" &&
        reservation->getReservedStatus() != "REFUNDED") {
      ranking[reservation->getReservedPlaysId()]++;
    }
  }
  return ranking;
}

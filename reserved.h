#ifndef RESERVED_H
#define RESERVED_H

#include <ctime>
#include <string>
#include <vector>

using namespace std;

class Reserved {
public:
  Reserved();
  ~Reserved();

  // Getters
  int getReservedId() const { return m_reservedId; }
  int getReservedPlaysId() const { return m_reservedPlaysId; }
  int getReservedCustomerId() const { return m_reservedCustomerId; }
  const vector<int> &getReservedSeats() const { return m_reservedSeat; }
  time_t getReservedDate() const { return m_reservedDate; }
  time_t getReservedTime() const { return m_reservedTime; }
  float getReservedPrice() const { return m_reservedPrice; }
  string getReservedStatus() const { return m_reservedStatus; }

  // Setters
  void setReservedId(int id) { m_reservedId = id; }
  void setReservedPlaysId(int id) { m_reservedPlaysId = id; }
  void setReservedCustomerId(int id) { m_reservedCustomerId = id; }
  void setReservedSeats(const vector<int> &seats) { m_reservedSeat = seats; }
  void setReservedDate(time_t date) { m_reservedDate = date; }
  void setReservedTime(time_t time) { m_reservedTime = time; }
  void setReservedPrice(float price) { m_reservedPrice = price; }
  void setReservedStatus(const string &status) { m_reservedStatus = status; }

private:
  int m_reservedId;
  int m_reservedPlaysId;
  int m_reservedCustomerId;
  vector<int> m_reservedSeat;
  time_t m_reservedDate;
  time_t m_reservedTime;
  float m_reservedPrice;
  string m_reservedStatus;
};
#endif // RESERVED_H

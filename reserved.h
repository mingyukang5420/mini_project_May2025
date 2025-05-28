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
  void getReservedId();
  int getReservedPlaysId();
  int getReservedCustomerId();
  int getReservedSeat();
  time_t getReservedDate();
  time_t getReservedTime();
  int getReservedPrice();
  string getReservedStatus();

private:
  int m_reservedId;
  int m_reservedPlaysId;
  int m_reservedCustomerId;
  vector<int> m_reservedSeat;
};
#endif // RESERVED_H

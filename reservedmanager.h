#ifndef RESERVEDMANAGER_H
#define RESERVEDMANAGER_H

#include "reserved.h"
#include "user.h"
#include <map>

class ReservedManager {
public:
  ReservedManager();
  ~ReservedManager();
  void addReserved();
  void removeReserved(int, const User *);
  // void cancelReserved(int, const User *); //Integrated removeReserved
  void modifyReserved(int, const User *);
  void viewReserved();
  int makeReservedId();
  Reserved *searchReserved(int);

private:
  map<int, Reserved *> reservedList;
};
#endif // RESERVEDMANAGER_H

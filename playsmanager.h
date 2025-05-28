#ifndef PLAYSMANAGER_H
#define PLAYSMANAGER_H
#include "plays.h"
#include "user.h"
#include <map>

class PlaysManager {
public:
  PlaysManager();
  ~PlaysManager();
  void addPlays();
  void removePlays(int, const User *);
  void modifyPlays(int, const User *);
  void viewPlays();
  int makePlaysId();
  Plays *searchPlays(int);

private:
  map<int, Plays *> playsList;
};

#endif // PLAYSMANAGER_H

#ifndef PLAYS_H
#define PLAYS_H

#include <string>
#include <vector>
using namespace std;

class Plays {
public:
  Plays();
  ~Plays();
  void getPlaysId();
  string getPlaysName();
  time_t getPlaysDate();
  time_t getPlaysTime();
  string getPlaysLocation();
  int getPlaysPrice();
  string getPlaysGenre();
  float getPlaysReviewScore();
  vector<string> getPlaysCast();
  int getPlaysRunningTime();

private:
  int m_playsId;
  string m_playsName;
  time_t m_playsDate;
  time_t m_playsTime;
  string m_playsLocation;
  int m_playsPrice;
  string m_playsGenre;
  float m_playsReviewScore;
  vector<string> m_playsCast;
  int m_playsRunningTime;
};

#endif // PLAYS_H
